gPlayTable = {}
gCurrentState = nil
gLastState  = nil
gLastPlay = nil
gCurrentPlay = nil
gRealState = nil
gLastCycle = 0

--for _, value in pairs(gRefPlay) do
--	local filename = LUA_SCRIPTS_REFPLAY_PATH .. value .. ".lua"
--	dofile(filename)
--end

for _, value in pairs(gTestPlay) do
	local filename = LUA_SCRIPTS_TESTPLAY_PATH .. value .. ".lua"
	local play = dofile(filename)
	if play ~= nil then
		gPlayTable[value] = play
	end
end

function gPlayTable.CreatePlay(spec)
	-- firstState作为脚本入口，不可缺少
	if spec.firstState ~= nil then
		-- 暂时不检测脚本内容
		for attr, attr_table in pairs(spec) do
			if type(attr_table) == "table" then
				if attr_table.match ~= nil then
					local role = {}
					for rolename, task in pairs(attr_table) do
						if rolename ~= "match" and rolename ~= "switch" then
							role.insert(rolename)
						end
					end
					attr_table.match = DecodeMatchStr(attr_table.match, role)
				end
			end
		end
		return spec
	end
end

function checkPlayENV()
	-- 视觉有问题，但跑任何脚本都一样，仅报告
	if vision:Cycle() - gLastCycle > 6 then
		debugEngine:gui_debug_msg(CGeoPoint:new_local(-param.pitchLength/2,-param.pitchWidth/2),"Error Vision Cycle",0)
	end
end

function NeedExit(name)
	-- 脚本名不存在，退出
	if type(name) ~= "string" or gPlayTable[name] == nil then
		debugEngine:gui_debug_msg(CGeoPoint:new_local(-param.pitchLength/2+100,-param.pitchWidth/2),"Error Play Name: "..name,0)
		return true
	end
	-- 正常状态退出
	local curPlay = gPlayTable[name]
	if gCurrentState == "finish" or gCurrentState == "exit" then
		return true
	end
	return false
end

function ResetPlay(name)
	local curPlay = gPlayTable[name]
	gRolePos = {}
	world:SPlayFSMSwitchClearAll(true)
	--------------------------------
	--added by thj for markingField
	defenceInfo:clearAll()
	defenceInfo:clearNoChangeFlag()
	defenceInfo:resetMarkingInfo()
	--DefendUtils.clearKickOffDefArea()
	--------------------------------
	gCurrentState = curPlay.firstState
	DoRolePosMatch(curPlay, true, false)
end

function RunPlay(name)
	local curPlay = gPlayTable[name]
	local curState = nil
	local isStateSwitched = false
	-- Play里的switch
	if type(curPlay.switch) == "function" then
		curState = curPlay:switch()
	else
		-- Play某个状态里的switch
		if gCurrentState ~= "exit" and gCurrentState ~= "finish" and type(curPlay[gCurrentState].switch) == "function" then
			curState = curPlay[gCurrentState]:switch()
		end
	end
	-- 完成状态切换
	if curState ~= nil then
		gLastState = gCurrentState
		gCurrentState = curState
		isStateSwitched = true
		world:SPlayFSMSwitchClearAll(true)
	end

	DoRolePosMatch(curPlay, false, isStateSwitched)
		
--~	Play中任务返回规则
--~	1 ---> task, 2 --> matchpos, 3--->kick, 4 --->dir, 5 --->pre, 6 --->kp, 7--->cp, 8--->flag
	kickStatus:clearAll()
	for rolename, task in pairs(curPlay[gRealState]) do
		if (type(task) == "function" and rolename ~= "match" and (gRoleNum[rolename] ~= nil or type(rolename)=="function")) then
			task = task(gRoleNum[rolename])
		end

		if (type(task) == "table" and rolename ~= "match" and (gRoleNum[rolename] ~= nil or type(rolename)=="function")) then
--~ 		统一进行射门和吸球的管理,并做任务处理
			if task[1] == nil then
				task = curPlay[gLastState][rolename]
			end

			local roleNum
			if type(rolename)=="string" then
				roleNum = gRoleNum[rolename]
				--print("Here in string : "..roleNum)
			elseif type(rolename)=="function" then
				roleNum = rolename()
				--print("Here in function : "..roleNum)
			end

			if roleNum ~= -1 then
				if task[3] ~= nil and task[3](roleNum) ~= kick.none() then
					local mkick = task[3](roleNum)
					local mdir = task[4](roleNum)
					local mpre = task[5](roleNum)
					local mkp  = task[6](roleNum)
					local mcp  = task[7](roleNum)
					local mflag = task[8]
					local isDirOk = world:KickDirArrived(vision:Cycle(), mdir, mpre, roleNum)
					-- if rolename == "Breaker" then
					-- 	print(player.dir("Breaker"), mdir, isDirOk, ball.toPlayerDist("Breaker"))
					-- end
					if isDirOk or bit:_and(mflag, flag.force_kick) ~= 0 then
						if mkick == kick.flat() then
							kickStatus:setKick(roleNum, mkp)
						elseif mkick == kick.chip() then
							kickStatus:setChipKick(roleNum, mcp)
						end
					end
				end
				if(type(rolename)=="string") then
					debugEngine:gui_debug_msg(vision:OurPlayer(roleNum):Pos(), string.sub(rolename, 1, 1))
				end
				-- 执行skill里的excute()
				task[1](roleNum)
			end
		end
	end
	gLastCycle = vision:Cycle()
end

function DoRolePosMatch(curPlay, isPlaySwitched, isStateSwitched)
	if (gCurrentState == "exit" or gCurrentState == "finish") and gLastState ~= nil then
		gRealState = gLastState
	else
		gRealState = gCurrentState
	end
	for rolename, task in pairs(curPlay[gRealState]) do
		-- 执行task，得出用于RoleMatch的点位
		-- 接受两类写法，一般是table，执行matchPos()，function可根据情况返回table
		if(type(task) == "function" and rolename ~= "match" and rolename~="switch") then
			task = task()
		end	
		if(type(task) == "table" and rolename ~= "match") then
			-- 特殊skill，保持上一状态的skill
			if task.name == "continue" and gCurrentState ~= "exit" and gCurrentState ~= "finish" and gLastState ~= nil then
				curPlay[gRealState][rolename] = {}
				for i,v in ipairs(curPlay[gLastState][rolename]) do
					table.insert(curPlay[gRealState][rolename], v)
				end
			end
			-- 执行skill里的matchPos()
			gRolePos[rolename] = curPlay[gRealState][rolename][2]()
		end
	end
	UpdateRole(curPlay[gRealState].match, isPlaySwitched, isStateSwitched)
end
