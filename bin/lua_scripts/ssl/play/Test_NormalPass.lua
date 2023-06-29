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
	if ball.posX() > 200 and ball.posY() < -120 then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "LeftFront"..ballStatus
		else 
			return "LeftFront"
		end
	elseif ball.posX() > 200 and ball.posY() < 120 then
			return "MiddleFront"
	elseif ball.posX() > 200 then
			return "RightFront"
	elseif ball.posX() > 0 and ball.posY() < -120 then
			return "LeftMiddleFront"
	elseif ball.posX() > 0 and ball.posY() < 120 then
			return "MiddleMiddleFront"
	elseif ball.posX() > 0 then
			return "RightMiddleFront"
	elseif ball.posX() > -200 and ball.posY() < -120 then
			return "LeftMiddleBack"
	elseif ball.posX() > -200 and ball.posY() < 120 then
			return "MiddleMiddleBack"
	elseif ball.posX() > -200 then
			return "RightMiddleBack"
	elseif ball.posY() < -120 then
			return "LeftBack"
	elseif ball.posY() < 120 then
			return "MiddleBack"
	elseif true then
			return "RightBack"
	end
end
local TEST = function()
	return "LeftFront"
end
-- Leader + Assister + Powerhouse
-- Special + Defender
-- Goalie + Middle + Hawk
gPlayTable.CreatePlay{

firstState = "LeftFront",

["LeftFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 2),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},

["LeftFrontOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 2),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},

["MiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 5),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},

["RightFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 3),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},

["LeftMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 2),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},

["MiddleMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 0),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},


["RightMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 3),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},

["LeftMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 2),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},
["MiddleMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 2),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},
["RightMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 0),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},

["LeftBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 2),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},
["MiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 2),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},
["RightBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader", 0),
	Hawk = task.protectBall(),
    match = "[L][AH]"
},
name = "Test_NormalPass",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
