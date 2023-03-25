local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_NOT_AVOID --+ flag.dribbling

local TargetPos1  = CGeoPoint:new_local(450,350)
local TargetPos2  = CGeoPoint:new_local(450,-350)
local TargetPos3  = CGeoPoint:new_local(-450,-350)
local TargetPos4  = CGeoPoint:new_local(-450,350)

local DIR1  = 1.57
local DIR2  = 1.57
local DIR3  = 1.57
local DIR4  = 1.57

local distThreshold = 50
local ACC = nil

gPlayTable.CreatePlay{

firstState = "run1",
["run1"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Goalie") < distThreshold , 100) then
			return "run2";
		end
	end,
	Goalie = task.goCmuRush(TargetPos2),
    -- Kicker = task.goCmuRush(TargetPos1, DIR, ACC, DSS),

    match = ""
},

["run2"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Goalie") < distThreshold , 300) then
			return "run1";
		end
	end,
	Goalie = task.goCmuRush(TargetPos3),
    -- Kicker = task.goCmuRush(TargetPos1, DIR, ACC, DSS),

    match = ""
},

["run3"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Goalie") < distThreshold , 300) then
			return "run1";
		end
	end,
	Goalie = task.goCmuRush(TargetPos4),
    -- Kicker = task.goCmuRush(TargetPos1, DIR, ACC, DSS),

    match = ""
},

name = "Test_Run",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}