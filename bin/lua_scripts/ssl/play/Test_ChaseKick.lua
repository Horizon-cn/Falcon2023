local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local distThreshold = 50

gPlayTable.CreatePlay{

firstState = "chase",

["chase"] = {
	switch = function ()
		if world:getBallPossession(true, gRoleNum["Kicker"]) > 0.3 then
		--if bufcnt(world:getBallToucher() == gRoleNum["Kicker"], 5) then
		--if bufcnt(robotSensor:IsInfraredOn(1), 5)then
			return "break";
		end
	end,
    
	Kicker = task.getBall(ball.pos()),
    match = ""
},
["break"] = {
	switch = function ()
		if world:getBallPossession(true, gRoleNum["Kicker"]) == 0 then
		--if bufcnt(world:getBallToucher() ~= gRoleNum["Kicker"], 10) then
		--if bufcnt(not robotSensor:IsInfraredOn(1), 10)then
			return "chase";
		end
	end,
    Kicker = task.testBreak(),
    match = ""
},

name = "Test_ChaseKick",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999

}