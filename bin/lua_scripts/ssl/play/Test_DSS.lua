local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_NOT_AVOID --+ flag.dribbling

local TargetPos1  = CGeoPoint:new_local(210,-255)
local TargetPos2  = CGeoPoint:new_local(210,-77)
local TargetPos3  = CGeoPoint:new_local(140,-140)
local TargetPos4  = CGeoPoint:new_local(280,-140)

local DIR1  = 1.57
local DIR2  = 1.57
local DIR3  = 1.57
local DIR4  = 1.57

local distThreshold = 10
local ACC = nil

gPlayTable.CreatePlay{

firstState = "run1",
["run1"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold and player.toTargetDist("Receiver") < distThreshold, 150, 1000) then
			return "run2";
		end
	end,
	Kicker = task.goCmuRush(TargetPos1, 1.57),
	Receiver = task.goCmuRush(TargetPos3, 1.57),
    match = ""
},

["run2"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold and player.toTargetDist("Receiver") < distThreshold, 150, 1000) then
			return "run1";
		end
	end,
	Kicker = task.goCmuRush(TargetPos2, 1.57),
	Receiver = task.goCmuRush(TargetPos4, 1.57),
    match = ""
},


name = "Test_DSS",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}