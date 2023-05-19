-- local STOP_POS1 = function()
-- 	if ball.toOurGoalDist() < 160*param.lengthRatio then
-- 		return CGeoPoint:new_local(-150*param.lengthRatio,0)
-- 	else
-- 		return ball.pos() + Utils.Polar2Vector(59, ball.toOurGoalDir())
-- 	end
-- end

-- local COR_DEF_POS1 = CGeoPoint:new_local(-50*param.lengthRatio,-50*param.widthRatio)

-- gPlayTable.CreatePlay{

-- firstState = "beginning",

-- switch = function()	
-- 	if gCurrentState == "beginning" and 
-- 		enemy.attackNum() <= 6 and enemy.attackNum() > 0 then
-- 		return "attacker"..enemy.attackNum()
-- 	else
-- 		if cond.isGameOn() then
-- 			return "finish"
-- 		elseif enemy.situChanged() and
-- 			enemy.attackNum() <= 6 and enemy.attackNum() > 0 then
-- 			return "attacker"..enemy.attackNum()
-- 		end
-- 	end
-- end,

-- ["beginning"] = {
-- 	Assister   = task.defendKick(),
-- 	Special  = task.defendHead(),
-- 	Middle   = task.goCmuRush(COR_DEF_POS1, player.toBallDir, _, flag.dodge_ball),
-- 	Defender = task.leftBack(),
-- 	Leader   = task.rightBack(),
-- 	Goalie   = task.goalieNew(),
-- 	match    = "[ADLSM]"
-- },

-- ["attacker1"] = {
-- 	Leader   = task.defendKick(),
-- 	Special  = task.marking("First"),
-- 	Assister = task.multiBack(3, 3),
-- 	Middle   = task.goSpeciPos(COR_DEF_POS1, player.toBallDir),
-- 	Defender = task.goSpeciPos(COR_DEF_POS2, player.toBallDir),
-- 	Goalie   = task.goalieNew(),
-- 	Engine   = task.multiBack(3, 1),
-- 	Hawk	 = task.multiBack(3, 2),
-- 	match    = "[L][DSM][AEH]"
-- },

-- ["attacker2"] = {
-- 	Leader   = task.defendKick(),
-- 	Defender = task.defendMiddleHead(),
-- 	Middle   = task.defendHead(),
-- 	Assister = task.marking("First"),
-- 	Special  = task.multiBack(3, 3),
-- 	Engine   = task.multiBack(3, 1),
-- 	Hawk	 = task.multiBack(3, 2),
-- 	Goalie   = task.goalieNew(),
-- 	match    = "[A][M][D][L][SEH]"
-- },

-- ["attacker3"] = {
-- 	Leader   = task.defendKick(),
-- 	Defender = task.defendMiddleHead(),
-- 	Middle   = task.sideBack(),
-- 	Assister = task.marking("First"),
-- 	Special  = task.marking("Second"),
-- 	Engine   = task.rightBack(),
-- 	Hawk	 = task.leftBack(),
-- 	Goalie   = task.goalieNew(),
-- 	match    = "[L][MEH][D][AS]"
-- },

-- ["attacker4"] = {
-- 	Leader   = task.defendKick(),
-- 	Defender = task.defendMiddleHead(),
-- 	Middle   = task.sideBack(),
-- 	Assister = task.marking("First"),
-- 	Special  = task.marking("Second"),
-- 	Engine   = task.rightBack(),
-- 	Hawk	 = task.leftBack(),
-- 	Goalie   = task.goalieNew(),
-- 	match    = "[L][MEH][D][AS]"
-- },

-- ["attacker5"] = {
-- 	Leader   = task.defendKick(),
-- 	Defender = task.defendMiddleHead(),
-- 	Middle   = task.sideBack(),
-- 	Assister = task.marking("First"),
-- 	Special  = task.marking("Second"),
-- 	Engine   = task.rightBack(),
-- 	Hawk	 = task.leftBack(),
-- 	Goalie   = task.goalieNew(),
-- 	match    = "[L][MEH][D][AS]"
-- },

-- ["attacker6"] = {
-- 	Leader   = task.defendKick(),
-- 	Defender = task.defendMiddleHead(),
-- 	Middle   = task.sideBack(),
-- 	Assister = task.marking("First"),
-- 	Special  = task.marking("Second"),
-- 	Engine   = task.rightBack(),
-- 	Hawk	 = task.leftBack(),
-- 	Goalie   = task.goalieNew(),
-- 	match    = "[L][MEH][D][AS]"
-- },

-- ["attacker7"] = {
-- 	Leader   = task.defendKick(),
-- 	Defender = task.goMMPassPos("Leader"),
-- 	Middle   = task.sideBack(),
-- 	Assister = task.marking("First"),
-- 	Special  = task.marking("Second"),
-- 	Engine   = task.rightBack(),
-- 	Hawk	 = task.leftBack(),
-- 	Goalie   = task.goalieNew(),
-- 	match    = "[L][MEH][D][AS]"
-- },

-- ["attacker8"] = {
-- 	Leader   = task.defendKick(),
-- 	Defender = task.goMMPassPos("Leader"),
-- 	Middle   = task.sideBack(),
-- 	Assister = task.marking("First"),
-- 	Special  = task.marking("Second"),
-- 	Engine   = task.rightBack(),
-- 	Hawk	 = task.leftBack(),
-- 	Goalie   = task.goalieNew(),
-- 	match    = "[L][MEH][D][AS]"
-- },

-- name = "Ref_Stop4CornerDef",
-- applicable ={
-- 	exp = "a",
-- 	a   = true
-- },
-- attribute = "defense",
-- timeout   = 99999
-- }

local STOP_POS1 = function()
	return ball.pos() + Utils.Polar2Vector(65, ball.toOurGoalDir())
	-- if ball.toOurGoalDist() < 160*param.lengthRatio then
	-- 	return CGeoPoint:new_local(-150*param.lengthRatio,0)
	-- else
	-- 	return ball.pos() + Utils.Polar2Vector(59, ball.toOurGoalDir())
	-- end
end

local COR_DEF_POS1 = CGeoPoint:new_local(-50*param.lengthRatio,-50*param.widthRatio)

gPlayTable.CreatePlay{

firstState = "beginning",

switch = function()	
	if gCurrentState == "beginning" then
		return "beginning"
	end
	if gCurrentState == "beginning" and 
		enemy.attackNum() <= 6 and enemy.attackNum() > 0 then
		return "attacker"..enemy.attackNum()
	else
		if cond.isGameOn() then
			return "finish"
		elseif enemy.situChanged() and
			enemy.attackNum() <= 6 and enemy.attackNum() > 0 then
			return "attacker"..enemy.attackNum()
		end
	end
end,

["beginning"] = {
	Assister   = task.goCmuRush(STOP_POS1, player.toBallDir, _, flag.dodge_ball),
	Special  = task.marking("First"),
	Middle   = task.defendHead(),
	Defender = task.leftBack(),
	Leader   = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[ADLSM]"
},

["attacker1"] = {
	Assister   = task.goCmuRush(STOP_POS1, player.toBallDir, _, flag.dodge_ball),
	Special  = task.marking("First"),
	Middle   = task.goCmuRush(COR_DEF_POS1, player.toBallDir, _, flag.dodge_ball),
	Defender = task.leftBack(),
	Leader   = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[ADLSM]"
},

["attacker2"] = {
	Assister   = task.goCmuRush(STOP_POS1, player.toBallDir, _, flag.dodge_ball),
	Special  = task.marking("First"),
	Middle   = task.goCmuRush(COR_DEF_POS1, player.toBallDir, _, flag.dodge_ball),
	Defender = task.defendHead(),
	Leader   = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[ADLSM]"
},

["attacker3"] = {
	Assister   = task.goCmuRush(STOP_POS1, player.toBallDir, _, flag.dodge_ball),
	Special  = task.marking("First"),
	Middle   = task.marking("Second"),
	Defender = task.goCmuRush(COR_DEF_POS1, player.toBallDir, _, flag.dodge_ball),
	Leader   = task.defendHead(),
	Goalie   = task.goalieNew(),
	match    = "[ALSMD]"
},

["attacker4"] = {
	Assister   = task.goCmuRush(STOP_POS1, player.toBallDir, _, flag.dodge_ball),
	Special  = task.marking("First"),
	Middle   = task.marking("Second"),
	Defender = task.marking("Third"),
	Leader   = task.defendHead(),
	Goalie   = task.goalieNew(),
	match    = "[ALSMD]"
},

["attacker5"] = {
	Assister   = task.goCmuRush(STOP_POS1, player.toBallDir, _, flag.dodge_ball),
	Special  = task.marking("First"),
	Middle   = task.marking("Second"),
	Defender = task.marking("Third"),
	Leader   = task.defendHead(),
	Goalie   = task.goalieNew(),
	match    = "[ALSMD]"
},

["attacker6"] = {
	Assister   = task.goCmuRush(STOP_POS1, player.toBallDir, _, flag.dodge_ball),
	Special  = task.marking("First"),
	Middle   = task.marking("Second"),
	Defender = task.marking("Third"),
	Leader   = task.defendHead(),
	Goalie   = task.goalieNew(),
	match    = "[ALSMD]"
},

name = "Ref0_Stop4CornerDef",
applicable ={
	exp = "a",
	a   = true
},
attribute = "defense",
timeout   = 99999
}