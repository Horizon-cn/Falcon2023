--注意发前场球时的头球位防守，取消默认跑位  和家平 2020/2/22
local MIDDLE_DEF_POS = function()
	return CGeoPoint:new_local(-70, 100*ball.antiY())
end

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
		if bufcnt(cond.canDefenceExit(), 2,100) then
			return "finish"
		end
	else
		if bufcnt(cond.canDefenceExit(), 2) then
			return "finish"
		elseif bufcnt(cond.isGameOn(), 5) then
			return "norPass"
		end
	end
end,

["beginning"] = {
	Leader   = task.defendKick(),
	Special  = task.goPassPos("Leader"),
	Middle   = task.defendHead(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][DASM]"
},

["attacker1"] = {
	Leader   = task.defendKick(),
	Special  = task.goPassPos("Leader"),
	Middle   = task.defendHead(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][DASM]"
},

["attacker2"] = {
	Leader   = task.defendKick(),
	Special  = task.marking("First"),
	Middle   = task.defendHead(),
	Defender = task.defendMiddleHead(),
	Assister = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][S][DA][M]"
},

["attacker3"] = {
	Leader   = task.defendKick(),
	Special  = task.marking("First"),
	Middle   = task.defendHead(),
	Defender = task.defendMiddleHead(),
	Assister = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][S][DA][M]"
},

["attacker4"] = {
	Leader   = task.defendKick(),
	Special  = task.marking("First"),
	Middle   = task.defendHead(),
	Defender = task.defendMiddleHead(),
	Assister = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][S][DA][M]"
},

["attacker5"] = {
	Leader   = task.defendKick(),
	Special  = task.marking("First"),
	Middle   = task.defendHead(),
	Defender = task.defendMiddleHead(),
	Assister = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][S][DA][M]"
},

["attacker6"] = {
	Leader   = task.defendKick(),
	Special  = task.marking("First"),
	Middle   = task.defendHead(),
	Defender = task.defendMiddleHead(),
	Assister = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][S][DA][M]"
},

["norPass"] = {
	Leader   = task.advance(),
	Special  = task.marking("First"),
	Middle   = task.marking("Second"),
	Defender = task.defendMiddleHead(),
	Assister = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][S][AD][M]"
},

["norDef"] = {
	Leader   = task.advance(),
	Special  = task.marking("First"),
	Middle   = task.marking("Second"),
	Defender = task.sideBack(),
	Assister = task.singleBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][S][AD][M]"
},

name = "Ref_BackDefV10",
applicable ={
	exp = "a",
	a   = true
},
attribute = "defense",
timeout   = 99999
}