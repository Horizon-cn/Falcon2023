local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local distThreshold = 50

gPlayTable.CreatePlay{

firstState = "defence",

["defence"] = {
	switch = function ()
		if true then
			return "defence";
		end
	end,
	Leader = task.multiBack(3, 2),
    Special = task.multiBack(3, 1),
	Assister = task.multiBack(3, 3),
	Goalie = task.goalieNew(),
    match = "[LSA]"
},

name = "Test_MultiBack",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}