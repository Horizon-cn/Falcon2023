local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local distThreshold = 50

gPlayTable.CreatePlay{

firstState = "touch",

["touch"] = {
	switch = function ()
		if bufcnt(true,100) then
			return "touch1";
		end
	end,
	Leader = task.dribbleTurn(0,5),
	match = "[LSM]"
},
["touch1"] = {
	switch = function ()
		if bufcnt(true,100) then
			return "touch2";
		end
	end,
	Leader = task.dribbleTurn(90,5),
	match = "[LSM]"
},
["touch2"] = {
	switch = function ()
		if bufcnt(true,100) then
			return "touch3";
		end
	end,
	Leader = task.dribbleTurn(180,5),
	match = "[LSM]"
},
["touch3"] = {
	switch = function ()
		if bufcnt(true,100) then
			return "touch";
		end
	end,
	Leader = task.dribbleTurn(270,5),
	match = "[LSM]"
},


name = "Test_TouchKick",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}

