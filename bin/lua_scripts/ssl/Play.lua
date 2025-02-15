metaadd = {}
function metaadd.__add(a, b)
	for _, value in ipairs(b) do
		table.insert(a, value)
	end
	return a
end
gPlay = setmetatable({}, metaadd)
gPlay = gPlay + gRefPlayTable + gTestPlayTable + gNorPlayTable

gPlayTable = {}
gTimeCounter = 0
gCurrentState = ""
gLastState  = ""
gLastPlay = ""
gCurrentPlay = ""
gRealState = ""
gLastCycle = 0
gLastRefMsg = ""
gActiveRole = {}
gIsOurIndirectKickExit = false

gCurrentBallStatus="None"
gLastBallStatus=""
gCurrentFieldArea="BackField"
gLastFieldArea=""

--gCurrentOurBallAction="None"
-----add by zhyaic 2014.5.22-----
gExternStopCycle = 0
gExternExitCycle = 0

function gPlay.Next()
	local index = 1
	return function()
		index = index + 1
		return gPlay[index % table.getn(gPlay) + 1]
	end
end

function split(inputstr, sep)
	if sep == nil then
		sep = "%s"
	end
	local t={}
	for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
		table.insert(t, str)
	end
	return t
end

function table_length(t)
  local length=0
  for k, v in pairs(t) do
    length=length+1
  end
  return length
end

function gPlayTable.CreatePlay(spec)
	assert(spec.firstState ~= nil)
	assert(type(spec.name) == "string")
	assert(spec.applicable ~= nil)
	assert(spec.attribute ~= nil)
	assert(type(spec.timeout) == "number")

	new_spec = {}
	new_spec.firstState = spec.firstState
	new_spec.switch = spec.switch
	new_spec.name = spec.name
	new_spec.applicable = spec.applicable
	new_spec.attribute = spec.attribute
	new_spec.timeout = spec.timeout
	-- print("init: "..spec.name)
	for attr, attr_table in pairs(spec) do
		if attr~="applicable" and type(attr_table) == "table" then
			assert(attr_table.match ~= nil)
			new_attr_table = {}
			for rolename, roletask in pairs(attr_table) do
				if type(rolename) ~= "function" and rolename ~= "switch" and string.find(rolename,"_") then
					roles = split(rolename,"_")
					assert(table_length(roles) == table_length(roletask))
					for i=1,table_length(roles) do
						new_attr_table[roles[i]] = roletask[i]
					end
				else
					new_attr_table[rolename] = roletask
				end
			end
			new_spec[attr] = new_attr_table
		end
	end

	gPlayTable[new_spec.name] = new_spec
end

function IsRoleActive(rolename)
	for _, name in pairs(gActiveRole) do
		if rolename == name then
			return true
		end
	end
	return false
end

function DoRolePosMatch(curPlay, isPlaySwitched, isStateSwitched)
	if gCurrentState == "exit" or gCurrentState == "finish" then
		gRealState = gLastState
	else
		gRealState = gCurrentState
	end
	gActiveRole = {}
	for rolename, task in pairs(curPlay[gRealState]) do
		if(type(task) == "function" and rolename ~= "match" and rolename~="switch") then
			task = task()
		end	
		if(type(task) == "table" and rolename ~= "match") then
			table.insert(gActiveRole, rolename)
			if task.name == "continue" and gCurrentState ~= "exit" and gCurrentState ~= "finish" then
				curPlay[gRealState][rolename] = {}
				for i,v in ipairs(curPlay[gLastState][rolename]) do
					table.insert(curPlay[gRealState][rolename], v)
				end
				curPlay[gRealState][rolename].name = "continue"
			end
			if type(rolename) == "function" then
				gRolePos[rolename()] = curPlay[gRealState][rolename][2]()
			else
				gRolePos[rolename] = curPlay[gRealState][rolename][2]()
			end
		end
	end
	UpdateRole(curPlay[gRealState].match, isPlaySwitched, isStateSwitched)
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
	if curPlay.firstState ~= nil then
		gCurrentState = curPlay.firstState
		DoRolePosMatch(curPlay, true, false)
	else
		print("Error in ResetPlay!!")
	end
	gTimeCounter = 0
end

function ResetPlayWithLastMatch(name)
	local curPlay = gPlayTable[name]
	world:SPlayFSMSwitchClearAll(true)
	if curPlay.firstState ~= nil then
		gCurrentState = curPlay.firstState
	else
		print("Error in ResetPlay!!")
	end
	gTimeCounter = 0
end

function RunPlay(name)
	if(gPlayTable[name] == nil) then
		print("Error Play Name In RunPlay: "..name)
	else
		debugEngine:gui_debug_msg(CGeoPoint:new_local(-50, -param.pitchWidth/2-20),gCurrentPlay)
		local curPlay = gPlayTable[name]
		local curState
--		gLastState = gCurrentState
		local isStateSwitched = false
		if curPlay.switch ~= nil then
			curState = curPlay:switch()
		else
			if gCurrentState ~= "exit" and gCurrentState ~= "finish" then
				curState = curPlay[gCurrentState]:switch()
				-- print("curState"..curState)
			end
			--gCurrentState = curPlay[gCurrentState]:switch()
		end

		-- if gCurrentState == nil then
		-- 	gCurrentState = gLastState
		if curState ~= nil then
			gLastState = gCurrentState
			gCurrentState = curState
			-- print ("		"..gLastState.." ------->>>>>>>>>>>>>>>"..gCurrentState)
			isStateSwitched = true
			world:SPlayFSMSwitchClearAll(true)
		end

		-- debugEngine:gui_debug_msg(vision:OurPlayer(gRoleNum[rolename]):Pos(), rolename)

		DoRolePosMatch(curPlay, false, isStateSwitched)
		
--~		Play中任务返回规则
--~		1 ---> task, 2 --> matchpos, 3--->kick, 4 --->dir, 5 --->pre, 6 --->kp, 7--->cp, 8--->flag
		kickStatus:clearAll()
		for rolename, task in pairs(curPlay[gRealState]) do
			if (type(task) == "function" and rolename ~= "match" and (gRoleNum[rolename] ~= nil or type(rolename)=="function")) then
				task = task(gRoleNum[rolename])
			end

			if (type(task) == "table" and rolename ~= "match" and (gRoleNum[rolename] ~= nil or type(rolename)=="function")) then
--~ 			统一进行射门和吸球的管理,并做任务处理
				if task[1] == nil then
					task = curPlay[gLastState][rolename]
				end

				local roleNum
				if type(rolename)=="string" then
					roleNum = gRoleNum[rolename]
					--print("Here in string : "..roleNum)
				elseif type(rolename)=="function" then
					roleNum = gRoleNum[rolename()]
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
					task[1](roleNum)
				end
			end
		end
		gTimeCounter = gTimeCounter + 1
	end
	gLastCycle = vision:Cycle()
end

function NeedExit(name)
	if name == "" then
		return false
	end
	if(gPlayTable[name] == nil) then
		print("Error Skill Name In NeedExit: "..name)
	else
		local curPlay = gPlayTable[name]
		if gCurrentState == "finish" or
			gCurrentState == "exit" or
			gTimeCounter > curPlay.timeout or
			vision:Cycle() - gLastCycle > 6 then
			gTimeCounter = 0
			return true
		end
	end
	return false
end
