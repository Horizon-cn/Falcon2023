--角球防守，加入defendMiddleHead 2020.7.30 和家平
--专门防守CorenerKick_Chinacup_v3 在球发出来后仍然保持对中场控制
local COR_DEF_POS1 = CGeoPoint:new_local(-170,-50)
local COR_DEF_POS2 = CGeoPoint:new_local(-170,50)
local COR_DEF_POS3 = CGeoPoint:new_local(-70,0)

gPlayTable.CreatePlay{

firstState = "beginning",

switch = function()
	if gCurrentState == "beginning" and 
		enemy.attackNum() <= 8 and enemy.attackNum() > 0 then
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
	Special  = task.marking("First"),
	Middle   = task.goSpeciPos(COR_DEF_POS1, player.toBallDir,flag.allow_dss),
	Defender = task.goSpeciPos(COR_DEF_POS2, player.toBallDir,flag.allow_dss),
	Assister = task.multiBack(3, 3),
	Goalie   = task.goalieNew(),
	Engine   = task.multiBack(3, 1),
	Hawk	 = task.multiBack(3, 2),
	match    = "[L][AEH][DSM]"
},

["attacker1"] = {
	Leader   = task.defendKick(),
	Special  = task.marking("First"),
	Assister = task.multiBack(3, 3),
	Middle   = task.goSpeciPos(COR_DEF_POS1, player.toBallDir,flag.allow_dss),
	Defender = task.goSpeciPos(COR_DEF_POS2, player.toBallDir,flag.allow_dss),
	Goalie   = task.goalieNew(),
	Engine   = task.multiBack(3, 1),
	Hawk	 = task.multiBack(3, 2),
	match    = "[L][AEH][DSM]"
},

["attacker2"] = {
	Leader   = task.defendKick(),
	Defender = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Assister = task.marking("First"),
	Special  = task.multiBack(3, 3),
	Engine   = task.multiBack(3, 1),
	Hawk	 = task.multiBack(3, 2),
	Goalie   = task.goalieNew(),
	match    = "[SEH][A][M][D][L]"
},

["attacker3"] = {
	Leader   = task.defendKick(),
	Defender = task.defendMiddleHead(),
	Middle   = task.sideBack(),
	Assister = task.marking("First"),
	Special  = task.marking("Second"),
	Engine   = task.singleBack(),
	Hawk	 = task.defendMiddleHead(),
	Goalie   = task.goalieNew(),
	match    = "[L][EHM][D][AS]"
},

["attacker4"] = {
	Leader   = task.defendKick(),
	Defender = task.defendMiddleHead(),
	Middle   = task.sideBack(),
	Assister = task.marking("First"),
	Special  = task.marking("Second"),
	Engine   = task.singleBack(),
	Hawk	 = task.defendMiddleHead(),
	Goalie   = task.goalieNew(),
	match    = "[L][EHM][D][AS]"
},

["attacker5"] = {
	Leader   = task.defendKick(),
	Defender = task.defendMiddleHead(),
	Middle   = task.sideBack(),
	Assister = task.marking("First"),
	Special  = task.marking("Second"),
	Engine   = task.singleBack(),
	Hawk	 = task.defendMiddleHead(),
	Goalie   = task.goalieNew(),
	match    = "[L][EHM][D][AS]"
},

["attacker6"] = {
	Leader   = task.defendKick(),
	Defender = task.defendMiddleHead(),
	Middle   = task.sideBack(),
	Assister = task.marking("First"),
	Special  = task.marking("Second"),
	Engine   = task.singleBack(),
	Hawk	 = task.defendMiddleHead(),
	Goalie   = task.goalieNew(),
	match    = "[L][EHM][D][AS]"
},

["attacker7"] = {
	Leader   = task.defendKick(),
	Defender = task.goMMPassPos("Leader"),
	Middle   = task.sideBack(),
	Assister = task.marking("First"),
	Special  = task.marking("Second"),
	Engine   = task.singleBack(),
	Hawk	 = task.defendMiddleHead(),
	Goalie   = task.goalieNew(),
	match    = "[L][EHM][D][AS]"
},

["attacker8"] = {
	Leader   = task.defendKick(),
	Defender = task.goMMPassPos("Leader"),
	Middle   = task.sideBack(),
	Assister = task.marking("First"),
	Special  = task.marking("Second"),
	Engine   = task.singleBack(),
	Hawk	 = task.defendMiddleHead(),
	Goalie   = task.goalieNew(),
	match    = "[L][EHM][D][AS]"
},

["norPass"] = {
	Leader   = task.advance(),
	Special  = task.marking("First"),
	Middle   = task.marking("Second"),
	Defender = task.defendMiddleHead(),
	Assister = task.singleBack(),
	Engine   = task.rightBack(),
	Hawk	 = task.leftBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][EHA][D][SM]"
},

["norDef"] = {
	Leader   = task.advance(),
	Special  = task.marking("First"),
	Middle   = task.marking("Second"),
	Defender = task.defendMiddleHead(),
	Assister = task.singleBack(),
	Engine   = task.rightBack(),
	Hawk	 = task.leftBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][EHA][D][SM]"
},

name = "Ref_CornerDefV5",
applicable ={
	exp = "a",
	a   = true
},
attribute = "defense",
timeout   = 99999
}
