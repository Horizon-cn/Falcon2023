local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local distThreshold = 50

gPlayTable.CreatePlay{

firstState = "protectBall",

["protectBall"] = {
	switch = function ()
		if true then
			return "protectBall";
		end
	end,
	Leader = task.advance(),
    Assister = task.protectBall(),
    match = "{LA}"
},

name = "Test_ProtectBall",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}