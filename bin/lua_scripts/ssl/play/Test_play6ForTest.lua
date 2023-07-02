local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local distThreshold = 50
local TargetPos1  = CGeoPoint:new_local(280,200)

local One = 200
local Two = 280

-- -200 200 
--   |   |   120
--   |   |  -120

local SwitchBallArea = function()
	if ball.posX() > 0  then
			return "Front"
	elseif ball.posX() < 0 then
			return "Back"
	end
end
local TEST = function()
	return "Front"
end
-- Leader + Assister + Powerhouse
-- Special + Defender
-- Goalie + Middle + Hawk
gPlayTable.CreatePlay{

firstState = "Front",

["Front"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 0),
	--Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADC]"
},

["Back"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 1),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	--Crosser = task.sifeBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADH]"
},

["RightFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront(),--task.support("Leader", 2),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADHC]"
},

["LeftMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 2),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADHC]"
},

["MiddleMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 0),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADHC]"
},


["RightMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 0),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADHC]"
},

["LeftMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 4),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADHC]"
},
["MiddleMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 4),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADHC]"
},
["RightMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 4),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADHC]"
},

["LeftBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 4),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADHC]"
},
["MiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 4),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADHC]"
},
["RightBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 4),
	Hawk = task.protectBall(),
	Defender = task.multiBack(1, 1),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][ADHC]"
},
name = "Test_play6ForTest",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
