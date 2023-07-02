local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling
local RECEIVE_POS = ball.syntYPos(CGeoPoint:new_local(100, 100))

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
	Leader   = task.markingFront("First"),
	Assister = task.sideBack(),
    Middle   = task.multiBack(4,4),
    Special  = task.advance(),
	Defender = task.multiBack(4,1),
	Breaker  = task.multiBack(4,2),
	Crosser  = task.multiBack(4,3),
	Goalie   = task.goalieNew(),
    match = "[S][DBC][LMA]"
},

name = "NormalPlayPureDefence8",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
