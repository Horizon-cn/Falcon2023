local DSS = flag.dodge_ball--bit:_or(flag.allow_dss,flag.dodge_ball)
local TargetPos1  = CGeoPoint:new_local(250,260)
local TargetPos2  = CGeoPoint:new_local(250,-260)
local TargetPos3  = CGeoPoint:new_local(100,-260)
local TargetPos4  = CGeoPoint:new_local(100,260)
local distThreshold = 10
local DIR  = 1.57
local ACC = nil
-- local BALL_PLACE_FLAG = flag.dodge_ball+flag.allow_dss+flag.their_baLL_placement

local goBezierRush = true
local MOVE_TASK = function(pos, dir, acc, flag)
	if goBezierRush then
		return task.goBezierRush(pos, dir, acc, flag)
	else
		return task.goCmuRush(pos, dir, acc, flag)
	end
end

gPlayTable.CreatePlay{

firstState = "run1",

["run1"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 10, 1000) then -- and player.toTargetDist("Receiver") < distThreshold then
			return "run2";
		end
	end,

    Kicker = MOVE_TASK(TargetPos1, DIR, ACC, DSS),
    -- Receiver = task.goCmuRush(TargetPos2, DIR, ACC, DSS),
    -- Goalie = task.goalie(),
    match = ""
    --match  = "[L][AB][CE][HFS][DM]"
},

["run2"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 10, 1000) then --and player.toTargetDist("Receiver") < distThreshold then
			return "run3";
		end
	end,
	Kicker  = MOVE_TASK(TargetPos2, DIR, ACC, DSS),
	-- Receiver = task.goCmuRush(TargetPos3, DIR, ACC, DSS),
	-- Goalie = task.goalie(),
	match = ""
},

["run3"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 10, 1000)then --and player.toTargetDist("Receiver") < distThreshold then
			return "run4";
		end
	end,
	Kicker  = MOVE_TASK(TargetPos3, DIR, ACC, DSS),
	-- Receiver = task.goCmuRush(TargetPos4, DIR, ACC, DSS),
	-- Goalie = task.goalie(),
	match = ""
},

["run4"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 10, 1000) then --and player.toTargetDist("Receiver") < distThreshold then
			return "run1";
		end
	end,
	Kicker  = MOVE_TASK(TargetPos4, DIR, ACC, DSS),
	-- Receiver = task.goCmuRush(TargetPos1, DIR, ACC, DSS),
	-- Goalie = task.goalie(),
	match = ""
},

name = "Test_BezierRun",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}

