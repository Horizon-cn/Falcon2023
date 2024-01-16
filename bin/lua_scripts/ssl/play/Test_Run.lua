local TargetPos1  = CGeoPoint:new_local(400, 250)
local TargetPos2  = CGeoPoint:new_local(-400,250)
local TargetPos3  = CGeoPoint:new_local(-400,-250)
local TargetPos4  = CGeoPoint:new_local(400,-250)

local DIR1  = 0
local DIR2  = 1.5
local DIR3  = 3
local DIR4	= -1.5

local distThreshold = 10

gPlayTable.CreatePlay{

firstState = "run1",
["run1"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 150, 1000) then
			return "run2";
		end
	end,
    Kicker = task.goCmuRush(TargetPos1, DIR1),

    match = ""
},

["run2"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 150, 1000) then
			return "run3";
		end
	end,
	Kicker = task.goCmuRush(TargetPos2, DIR2),

    match = ""
},

["run3"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 150, 1000) then
			return "run4";
		end
	end,
	Kicker = task.goCmuRush(TargetPos3, DIR3),

    match = ""
},

["run4"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 150, 1000) then
			return "run1"	;
		end
	end,
	Kicker = task.goCmuRush(TargetPos4, DIR4),

    match = ""
},

-- ["run5"] = {
-- 	switch = function ()
-- 		if bufcnt(player.toTargetDist("Kicker") < distThreshold , 150, 1000) then
-- 			return "run1"	;
-- 		end
-- 	end,
-- 	Kicker = task.goCmuRush(TargetPos4, DIR4),

--     match = ""
-- },
name = "Test_Run",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}