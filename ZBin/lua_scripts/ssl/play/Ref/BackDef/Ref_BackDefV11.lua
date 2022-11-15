--注意发前场球时的头球位防守，取消盯防 防守区域  和家平 2020/2/22
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
	Special  = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalie(),
	match    = "[L][DASM]"
},

["attacker1"] = {
	Leader   = task.defendKick(),
	Special  = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalie(),
	match    = "[L][DASM]"
},

["attacker2"] = {
	Leader   = task.defendKick(),
	Special  = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalie(),
	match    = "[L][AD][S][M]"--"[L][S][M][AD]"
},

["attacker3"] = {
	Leader   = task.defendKick(),
	Special  = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalie(),
	match    = "[L][AD][S][M]" --"[L][S][M][AD]"
},

["attacker4"] = {
	Leader   = task.defendKick(),
	Special  = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalie(),
	match    = "[L][AD][S][M]"--"[L][S][M][AD]"
},

["attacker5"] = {
	Leader   = task.defendKick(),
	Special  = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalie(),
	match    = "[L][AD][S][M]"--"[L][S][M][AD]"
},

["attacker6"] = {
	Leader   = task.defendKick(),
	Special  = task.defendMiddleHead(),
	Middle   = task.defendHead(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalie(),
	match    = "[L][AD][S][M]"--"[L][S][M][AD]"
},

["norPass"] = {
	Leader   = task.advance(),
	Special  = task.marking("First"),
	Middle   = task.sideBack(),
	Defender = task.singleBack(),
	Assister = task.defendMiddleHead(),
	Goalie   = task.goalie(),
	match    = "[L][S][AD][M]"
},

["norDef"] = {
	Leader   = task.advance(),
	Special  = task.marking("First"),
	Middle   = task.sideBack(),
	Defender = task.singleBack(),
	Assister = task.defendMiddleHead(),
	Goalie   = task.goalie(),
	match    = "[L][S][AD][M]"
},

name = "Ref_BackDefV11",
applicable ={
	exp = "a",
	a   = true
},
attribute = "defense",
timeout   = 99999
}