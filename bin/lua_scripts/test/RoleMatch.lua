gRoleNum = {}
gLastRoleNum = {}
gRoleFixNum = {}
gRolePos = {}
gOurExistNum = {}
gRoleLookUpTable = {
-- 角色分为两类
-- 第一类为在gRolePriority和gRoleFixNum中进行真实车号配置的
["G"] = "Goalie",
["K"] = "Kicker",
["T"] = "Tier",
["R"] = "Receiver",

-- 第二类为在脚本中可能会发生匹配变化的角色
["A"] = "Assister",
["B"] = "Breaker",
["C"] = "Crosser",
["D"] = "Defender",
["E"] = "Engine",
["F"] = "Finisher",
["H"] = "Hawk",
["L"] = "Leader",
["M"] = "Middle",
["P"] = "Powerhouse",
["S"] = "Special"
}

function DecodeMatchStr(matchRule, matchRole) -- 解析match字符串
	local strTable = {}
	local teamCnt = 1
	local str
	if type(matchRule) == "function" then 
		str = matchRule()
	elseif type(matchRule) == "string" then
		str = matchRule
	else 
		print("RoleMatch:not a valid matchRule type!! "..type(matchRule))
		-- print(matchRule)
	end
	while true do
		local character = string.sub(str, 1, 1)
		local endChar
		local mode
		if character == '[' then
			endChar = ']'
			mode = "RealTime"
		elseif character == '(' then
			endChar = ')'
			mode = "Once"
		elseif character == '{' then
			endChar = '}'
			mode = "Never"
		else
			break
		end

		local endPos, _ = string.find(str, endChar)
		local teamTable = {}
		for subIndex = 2, endPos-1 do -- 插入所有需要匹配的角色
			local char = string.sub(str, subIndex, subIndex)
			for _, rolename in matchRole do 
				if char == string.sub(rolename, 1, 1) then
					table.insert(teamTable, rolename)
					break
				end
			end
		end
		teamTable["mode"] = mode
		strTable[teamCnt] = teamTable
		teamCnt = teamCnt + 1 -- 一个match中可写多个括号
		str = string.sub(str,endPos+1)
		if str == "" then break end
	end
	return strTable
end

function DoFixNumMatch(fixNum)
	for i = 0, param.maxPlayer - 1 do
		if gOurExistNum[i] == fixNum then
			gOurExistNum[i] = -1
			return i
		end
	end
	return -1
end

function GetMatchPotential(num, role)
	local vec = player.pos(num) - gRolePos[role]
    return vec:mod2() / 4.0
end

function DoMunkresMatch(rolePos)
	local nrows = table.getn(rolePos)
	local ncolsIndex = {}
	local ncols = 0 --table.getn(gOurExistNum)
	for i = 0, param.maxPlayer - 1 do
		if gOurExistNum[i] ~= -1 then
			ncols = ncols + 1
			ncolsIndex[ncols] = i
		end
	end
	local matrix = Matrix_double_:new_local(nrows, ncols)
	for row = 1, nrows do
		for col = 1, ncols do
			matrix:setValue(row-1, col-1, GetMatchPotential(gOurExistNum[ncolsIndex[col]], rolePos[row]))
		end
	end

	local m = Munkres:new_local()
	m:solve(matrix)

	local eraseList = {}
	for row = 1, nrows do	
		for col = 1, ncols do
			if matrix:getValue(row-1, col-1) == 0 then
--~ 				print(rolePos[row], gOurExistNum[col])
				gRoleNum[rolePos[row]] = gOurExistNum[ncolsIndex[col]]
				table.insert(eraseList, gOurExistNum[ncolsIndex[col]])
				break
			end
		end
	end

	for _, value in ipairs(eraseList) do
		RemoveExistNum(value)
	end
end

function RemoveExistNum(num)
	gOurExistNum[num] = -1
end

function UpdateRole(matchTactic, isPlaySwitched, isStateSwitched)
	--if isPlaySwitched then
		gRoleNum = {}
	--end

	-- 为了使车号统一从0开始
	-- 但这样lua的table接口全都无法使用，所以只能强行trick放弃代码简洁性保证功能
	for i = 0, param.maxPlayer - 1 do
		if player.valid(i) then -- todo
			gOurExistNum[i] = i -- table.insert(ourExistNum, i)
		else
			gOurExistNum[i] = -1
		end
	end

	for rolename, roleID in pairs(gRoleFixNum) do
		for existname, _ in pairs(gRolePos) do
			if rolename == existname and type(roleID) == "number" then
				gRoleNum[rolename] = DoFixNumMatch(roleID)
				if rolename == "Goalie" then
					CRegisterRole(gRoleNum[rolename], "goalie")
				end
			end
		end
	end
	
	local matchList = {}
	for tactic, value in pairs(matchTactic) do -- 依次处理match中的括号
		if value.mode == "RealTime" or isPlaySwitched or
			(isStateSwitched and value.mode == "Once") then -- 重新匹配
			table.insert(matchList, value)
		else
			for _, rolename in ipairs(value) do -- 沿用上一周期的匹配
				gRoleNum[rolename] = gLastRoleNum[rolename]
				RemoveExistNum(gRoleNum[rolename])
			end
		end
	end
	
	for _, value in ipairs(matchList) do -- value -> 需要匹配的角色名表，依次处理match里的括号
		local role = {}
		local canMatchNum = 0 --table.getn(gOurExistNum)
		for i = 0, param.maxPlayer - 1 do -- 核查场上有多少车还没匹配
			if gOurExistNum[i] ~= -1 then
				canMatchNum = canMatchNum + 1
			end
		end
		for index = 1, table.getn(value) do -- 一个括号内的处理，按先后开始匹配，lua里的数组从1开始
			local haveMatchRobot = false
			if canMatchNum > 0 then -- 有足够的车可以匹配
				for rolename, pos in pairs(gRolePos) do
					if value[index] == rolename then  -- 确定该角色需要匹配(有mpos)
						canMatchNum = canMatchNum - 1
						table.insert(role, rolename)
						haveMatchRobot = true
						break
					end
				end
			end
			if not haveMatchRobot then
				gRoleNum[value[index]] = -1
			end
		end
		DoMunkresMatch(role) -- 匹配
	end
	
	gLastRoleNum = gRoleNum	
end
