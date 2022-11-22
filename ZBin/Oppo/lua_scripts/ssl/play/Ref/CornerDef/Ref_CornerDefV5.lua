--角球防守，加入defendMiddleHead 2020.7.30 和家平
--专门防守CorenerKick_Chinacup_v3 在球发出来后仍然保持对中场控制
local COR_DEF_POS1 = CGeoPoint:new_local(-170,-50)
local COR_DEF_POS2 = CGeoPoint:new_local(-170,50)
local COR_DEF_POS3 = CGeoPoint:new_local(-70,0)

gPlayTable.CreatePlay{

firstState = "beginning",

switch = function()
	if gCurrentState == "beginning" and 
		enemy.attackNum() <= 6 and enemy.attackNum() > 0 then
		return "attacker"..enemy.attackNum()
	elseif gCurrentState == "norPass" then
		if bufcnt(ball.velMod() < gNorPass2NorDefBallVel 
			or not enemy.hasReceiver(), 2) then
			return "norDef"
		end
	elseif gCurrentState == "norDef" then
		if bufcnt(cond.canDefenceExit(), 2,60) then
			return "finish"
		end
	else
		if bufcnt(cond.canDefenceExit(), 2) then
			return "finish"
		elseif enemy.situChanged() and 
			enemy.attackNum() <= 6 and enemy.attackNum() > 0 then
			return "attacker"..enemy.attackNum()
		elseif bufcnt(cond.isGameOn(), 5) then
			return "norPass"
		end
	end
end,

["beginning"] = {
	Leader   = task.defendKick(),
	Special  = task.goPassPos("Leader"),
	Middle   = task.goSpeciPos(COR_DEF_POS1, player.toBallDir),
	Defender = task.goSpeciPos(COR_DEF_POS2, player.toBallDir),
	Assister = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][DASM]"
},

["attacker1"] = {
	Leader   = task.defendKick(),
	Special  = task.rightBack(),
	Assister = task.leftBack(),
	Middle   = task.goSpeciPos(COR_DEF_POS1, player.toBallDir),
	Defender = task.goSpeciPos(COR_DEF_POS2, player.toBallDir),
	Goalie   = task.goalieNew(),
	match    = "[L][DASM]"
},

["attacker2"] = {
	Leader   = task.defendKick(),
	Defender = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Assister = task.marking("First"),
	Special  = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[A][M][D][L][S]"
},

["attacker3"] = {
	Leader   = task.defendKick(),
	Defender = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Assister = task.marking("First"),
	Special  = task.marking("Second"),
	Goalie   = task.goalieNew(),
	match    = "[M][D][A][LS]"
},

["attacker4"] = {
	Leader   = task.defendKick(),
	Defender = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Assister = task.marking("First"),
	Special  = task.marking("Second"),
	Goalie   = task.goalieNew(),
	match    = "[M][D][A][LS]"
},

["attacker5"] = {
	Leader   = task.defendKick(),
	Defender = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Assister = task.marking("First"),
	Special  = task.marking("Second"),
	Goalie   = task.goalieNew(),
	match    = "[M][D][A][LS]"
},

["attacker6"] = {
	Leader   = task.defendKick(),
	Defender = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Assister = task.marking("First"),
	Special  = task.marking("Second"),
	Goalie   = task.goalieNew(),
	match    = "[M][D][A][LS]"
},

["norPass"] = {
	Leader   = task.advance(),
	Special  = task.markingFront("First"),
	Middle   = task.markingFront("Second"),
	Defender = task.defendMiddleHead(),
	Assister = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][S][D][MA]"
},

["norDef"] = {
	Leader   = task.advance(),
	Special  = task.markingFront("First"),
	Middle   = task.markingFront("Second"),
	Defender = task.defendMiddleHead(),
	Assister = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][S][D][MA]"
},

name = "Ref_CornerDefV5",
applicable ={
	exp = "a",
	a   = true
},
attribute = "defense",
timeout   = 99999
}
