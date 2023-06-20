local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_NOT_AVOID --+ flag.dribbling
local DSS=flag.allow_dss

local TargetPos1  = CGeoPoint:new_local(112,190)
local TargetPos2  = CGeoPoint:new_local(330,190)
local TargetPos3  = CGeoPoint:new_local(300,-200)
local TargetPos4  = CGeoPoint:new_local(-100,200)

local DIR1  = 0


local distThreshold = 10
local ACC = nil

gPlayTable.CreatePlay{

firstState = "run1",
["run1"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 150, 1000) then
			return "run2";
		end
	end,
	Kicker = task.goCmuRush(TargetPos1, -1.57),
    -- Kicker = task.goCmuRush(TargetPos1, DIR, ACC, DSS),

    match = ""
},

["run2"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 150, 1000) then
			return "run1";
		end
	end,
	Kicker = task.goCmuRush(TargetPos2, -1.57),
    -- Kicker = task.goCmuRush(TargetPos1, DIR, ACC, DSS),

    match = ""
},

["run3"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 150, 1000) then
			return "run4";
		end
	end,
	Kicker = task.goCmuRush(TargetPos3, DIR1),
    -- Kicker = task.goCmuRush(TargetPos1, DIR, ACC, DSS),

    match = ""
},

["run4"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 150, 1000) then
			return "run5"	;
		end
	end,
	Kicker = task.goCmuRush(TargetPos4, DIR1),
    -- Kicker = task.goCmuRush(TargetPos1, DIR, ACC, DSS),

    match = ""
},

["run5"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 150, 1000) then
			return "run1"	;
		end
	end,
	Kicker = task.goCmuRush(TargetPos1, DIR1),
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