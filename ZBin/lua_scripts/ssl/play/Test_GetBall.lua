local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling
local READY_POS  = CGeoPoint:new_local(300,100)
local TargetPos  = CGeoPoint:new_local(-400,200)
local distThreshold = 50

gPlayTable.CreatePlay{

firstState = "getball",

["getball"] = {
		switch = function ()
			if bufcnt(player.toTargetDist("Receiver")<40 and
				player.toTargetDist("Goalie")<10, 3, 180) then
				return "chippass"
			end
		end,
		Receiver = task.getBall(),
		Goalie = task.goCmuRush(READY_POS),
		match    = ""
},

["chippass"] = {
		switch = function ()
			if player.kickBall("Receiver") then
				return "receive"
			end
		end,
		Receiver = task.passToPos(TargetPos, 450),
		Goalie = task.goCmuRush(READY_POS),
		match    = ""
},

["receive"] = {
		switch = function ()
			if true then
				return "receive"
			end
		end,
		Receiver = task.stop(),
		Goalie = task.getBall(),
		match    = ""
},

name = "Test_GetBall",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}