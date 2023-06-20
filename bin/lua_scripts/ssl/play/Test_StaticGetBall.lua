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
			if bufcnt(true) then
				return "getball"
			end
		end,
		--Receiver = task.getBall(),
		Kicker = task.staticGetBall(0),
		match    = ""
},



name = "Test_StaticGetBall",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}