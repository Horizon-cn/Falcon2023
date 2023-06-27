local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling
local RECEIVE_POS = ball.syntYPos(CGeoPoint:new_local(100, 100))

local distThreshold = 50
local TargetPos1  = CGeoPoint:new_local(280,200)
gPlayTable.CreatePlay{

firstState = "PureDefenceTo",

["PureDefenceTo"] = {
	switch = function ()
		if bufcnt(ball.toPlayerHeadDist("Assister") < 5, "fast", 180) then
			return "PureDefenceKick";
		end
	end,
	Leader   = task.marking("First"),
	Assister = task.marking("Second"),
    Middle   = task.marking("Third"),
    Special  = task.staticGetBall(RECEIVE_POS),
	Defender = task.multiBack(3,1),
	Breaker  = task.multiBack(3,2),
	Crosser  = task.multiBack(3,3),
	Goalie   = task.goalieNew(),
    match = "[S][DBC][LMA]"
},

["PureDefenceKick"] = {
	switch = function ()
		if bufcnt(player.kickBall("Special"), 10, 180) then
			return "PureDefenceTo";
		end
	end,
	Leader   = task.marking("First"),
	Assister = task.marking("Second"),
    Middle   = task.marking("Third"),
    Special  = task.justKick(),
	Defender = task.multiBack(3,1),
	Breaker  = task.multiBack(3,2),
	Crosser  = task.multiBack(3,3),
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
