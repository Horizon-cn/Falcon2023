local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_NOT_AVOID + flag.dribbling

local TargetPos1  = CGeoPoint:new_local(-50,150)
local TargetPos2  = CGeoPoint:new_local(330,150)
local distThreshold = 50
local DIR  = 1.57
local ACC = nil

gPlayTable.CreatePlay{

firstState = "passpos0",

["passpos0"] = {
	switch = function ()
		if bufcnt(player.kickBall("Receiver"), "fast") then
			return "passpos1";
		end
	end,
    Kicker = task.goCmuRush(TargetPos1, player.toPlayerDir("Receiver"), ACC, FLAG),
    Receiver = task.passToPos(TargetPos1, 300),
    match = ""
},

["passpos1"] = {
	switch = function ()
		if bufcnt(player.kickBall("Kicker"), "fast") then
			return "passpos0";
		end
	end,
    Kicker = task.passToPos(TargetPos2, 300),
    Receiver = task.goCmuRush(TargetPos2, player.toPlayerDir("Kicker"), ACC, FLAG),
    match = ""
},

name = "Test_PassNormal",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}