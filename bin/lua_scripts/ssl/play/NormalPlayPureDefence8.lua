local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local distThreshold = 50
local TargetPos1  = CGeoPoint:new_local(280,200)
gPlayTable.CreatePlay{

firstState = "PureDefence",

["PureDefence"] = {
	switch = function ()
		if true then
			return "PureDefence";
		end
	end,
	Leader   = task.marking("First"),
	Assister = task.marking("Second"),
    Middle   = task.marking("Third"),
    Special  = task.multiBack(4,1),
	Defender = task.multiBack(4,2),
	Breaker  = task.multiBack(4,3),
	Crosser  = task.multiBack(4,4),
	Goalie   = task.goalieNew(),
    match = "[LMA][SDBC]"
},

name = "NormalPlayPureDefence8",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
