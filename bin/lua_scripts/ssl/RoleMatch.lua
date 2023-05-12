gRoleNum = {
	["Goalie"] = -1,
	["Kicker"] = -1,
	["Tier"] = -1,
	["Receiver"] = -1,

	["Assister"] = -1,
	["Breaker"] = -1,
	["Crosser"] = -1,
	["Defender"] = -1,
	["Engine"] = -1,
	["Finisher"] = -1,
	["Hawk"] = -1,
	["Leader"] = -1,
	["Middle"] = -1,
	["Powerhouse"] = -1,
	["Special"] = -1
}

gLastRoleNum = {

}

gRolePos = {

}

gRolePriority = { "Goalie","Kicker","Tier","Receiver"}
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

function DecodeMatchStr(matchRule) -- 解析match字符串
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
			table.insert(teamTable, gRoleLookUpTable[string.sub(str, subIndex, subIndex)])
		end
		teamTable["mode"] = mode
		strTable[teamCnt] = teamTable
		teamCnt = teamCnt + 1 -- 一个match中可写多个括号
		str = string.sub(str,endPos+1)
		if str == "" then break end
	end
	return strTable
end

function GetMatchPotential(num, role)
	local vec = player.pos(num) - gRolePos[role]
    return vec:mod2() / 4.0
end

function RemoveExistNum(num)
	gOurExistNum[num] = -1
end

function DoRoleMatchReset(str)
	-- 循环获得需要重新匹配的角色
	while true do
		local character = string.sub(str, 1, 1)
		
		if character ~= '[' then
			break
		end

		local endPos, _ = string.find(str, ']')
		local roleTable = {}
		local numTable = {}
		for subIndex = 2, endPos-1 do
			local roleNameStr = gRoleLookUpTable[string.sub(str, subIndex, subIndex)]
			table.insert(roleTable, roleNameStr)
			table.insert(numTable, gRoleNum[roleNameStr])
		end

		-- 开始对每个分组进行重新的匹配
		local nrows = table.getn(roleTable)
		local ncols = table.getn(numTable)
		local matrix = Matrix_double_:new_local(nrows, ncols)
		for row = 1, nrows do
			for col = 1, ncols do
				matrix:setValue(row-1, col-1, GetMatchPotential(numTable[col], roleTable[row]))
			end
		end

		local m = Munkres:new_local()
		m:solve(matrix)

		for row = 1, nrows do
			for col = 1, ncols do
				if matrix:getValue(row-1, col-1) == 0 then
					gRoleNum[roleTable[row]] = numTable[col]				
					break
				end
			end
		end

		str = string.sub(str,endPos+1)
		if str == "" then break end
	end
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


function DoFixNumMatch(fixNums)
	for _, fixNum in ipairs(fixNums) do
		for i = 0, param.maxPlayer - 1 do
			if gOurExistNum[i] == fixNum then
				gOurExistNum[i] = -1
				return i
			end
		end
	end
	return -1
end

function SetNoMatchRoleZero()
	for _, rolename in pairs(gRoleLookUpTable) do
		if gRoleNum[rolename] == nil then
			gRoleNum[rolename] = -1
		end
	end	
end

function UpdateRole(matchTactic, isPlaySwitched, isStateSwitched)
	if isPlaySwitched then
		gRoleNum = {}
	end
	-- print("---------------------------------")

	-- 为了使车号统一从0开始
	-- 但这样lua的table接口全都无法使用，所以只能强行trick放弃代码简洁性保证功能
	for i = 0, param.maxPlayer - 1 do
		if player.valid(i) then
			gOurExistNum[i] = i -- table.insert(ourExistNum, i)
		else
			gOurExistNum[i] = -1
		end
	end

	local forceMatchGoalie = false
	-- 0号在场，强制匹配门将
	if gOurExistNum[0] == 0 then
		gRoleNum["Goalie"] = DoFixNumMatch({0})
		CRegisterRole(gRoleNum["Goalie"], "goalie")
		forceMatchGoalie = true
	end

	-- 处理固定匹配
	for rolename, id in pairs(gRoleFixNum) do
		for existname, _ in pairs(gRolePos) do
			if rolename == existname and type(id) == "table" then
				if rolename ~= "Goalie" then
					gRoleNum[rolename] = DoFixNumMatch(id)
				elseif forceMatchGoalie == false then
					gRoleNum[rolename] = DoFixNumMatch(id)
					CRegisterRole(gRoleNum["Goalie"], "goalie")
				end
			end
		end
	end

	for existname, _ in pairs(gRolePos) do
		if type(existname) == "number" then
			if existname >= 0 and existname < param.maxPlayer and gOurExistNum[existname] == existname then
				gOurExistNum[existname] = -1
				gRoleNum[existname] = existname
			else
				gRoleNum[existname] = -1
			end
		end
	end
	
	local matchList = {}
	matchTactic = DecodeMatchStr(matchTactic)
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
	
	SetNoMatchRoleZero()
	gLastRoleNum = gRoleNum	
end
