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
			return "LeftFront"
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
	
-- Leader + Assister + Powerhouse
-- Special + Defender
-- Goalie + Middle + Hawk
gPlayTable.CreatePlay{

firstState = "LeftFront",

["LeftFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"),
	Powerhouse = task.goRWPassPos("Leader"),
    Special = task.protectBall(),
    Defender = task.goMMPassPos("Leader"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][SAPD][HM]"
},

["MiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLWPassPos("Leader"),
	Powerhouse = task.goRWPassPos("Leader"),
    Special = task.protectBall(),
    Defender = task.goMWPassPos("Leader"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][SAPD][HM]"
},

["RightFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLWPassPos("Leader"),
	Powerhouse = task.goMWPassPos("Leader"),
    Special = task.protectBall(),
    Defender = task.goMMPassPos("Leader"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][SAPD][HM]"
},

["LeftMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLWPassPos("Leader"),
	Powerhouse = task.goMWPassPos("Leader"),
    Special = task.goMMPassPos("Leader"),
    Defender = task.protectBall(),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DAPS][HM]"
},

["MiddleMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLWPassPos("Leader"),
	Powerhouse = task.goMWPassPos("Leader"),
    Special = task.goRWPassPos("Leader"),
    Defender = task.protectBall(),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DAPS][HM]"
},


["RightMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"),
	Powerhouse = task.goRWPassPos("Leader"),
    Special = task.protectBall(),
    Defender = task.goMMPassPos("Leader"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][SAPD][HM]"
},

["LeftMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"),
	Powerhouse = task.markingFront("First"),
    Special = task.markingFront("Second"),
    Defender = task.protectBall(),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][HM][APSD]"
},
["MiddleMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"),
	Powerhouse = task.markingFront("Second"),
    Special = task.markingFront("First"),
    Defender = task.protectBall(),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},
["RightMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"),
	Powerhouse = task.markingFront("First"),
    Special = task.markingFront("Second"),
    Defender = task.protectBall(),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][HM][PS][AD]"
},

["LeftBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMMPassPos("Leader"),
	Powerhouse = task.markingFront("First"),
    Special = task.leftBack(),
    Defender = task.markingFront("Second"),
    Hawk = task.rightBack(),
	Middle = task.goMWPassPos("Leader"),
	Goalie = task.goalieNew(),
    match = "[L][AM][SH][PD]"
},
["MiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMMPassPos("Leader"),
	Powerhouse = task.markingFront("First"),
    Special = task.leftBack(),
    Defender = task.markingFront("Second"),
    Hawk = task.rightBack(),
	Middle = task.goMWPassPos("Leader"),
	Goalie = task.goalieNew(),
    match = "[L][AM][SH][PD]"
},
["RightBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMMPassPos("Leader"),
	Powerhouse = task.markingFront("First"),
    Special = task.leftBack(),
    Defender = task.markingFront("Second"),
    Hawk = task.rightBack(),
	Middle = task.goMWPassPos("Leader"),
	Goalie = task.goalieNew(),
    match = "[L][AM][SH][PD]"
},
name = "Test_NormalAttack",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
