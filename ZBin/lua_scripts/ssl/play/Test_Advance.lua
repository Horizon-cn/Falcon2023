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
    Special = task.goLMPassPos("Leader"),
    Defender = task.goMMPassPos("Leader"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][APSD][HM]"
},

["MiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLWPassPos("Leader"),
	Powerhouse = task.goRWPassPos("Leader"),
    Special = task.goLMPassPos("Leader"),
    Defender = task.goMMPassPos("Leader"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][APSD][HM]"
},

["RightFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLWPassPos("Leader"),
	Powerhouse = task.goMWPassPos("Leader"),
    Special = task.goLMPassPos("Leader"),
    Defender = task.goMMPassPos("Leader"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][APSD][HM]"
},

["LeftMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLWPassPos("Leader"),
	Powerhouse = task.goMWPassPos("Leader"),
    Special = task.goMMPassPos("Leader"),
    Defender = task.goRMPassPos("Leader"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][APSD][HM]"
},

["MiddleMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLWPassPos("Leader"),
	Powerhouse = task.goMWPassPos("Leader"),
    Special = task.goRWPassPos("Leader"),
    Defender = task.goLMPassPos("Leader"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][APSD][HM]"
},


["RightMiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"),
	Powerhouse = task.goRWPassPos("Leader"),
    Special = task.goLMPassPos("Leader"),
    Defender = task.goMMPassPos("Leader"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][APSD][HM]"
},

["LeftMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLMPassPos("Leader"),
	Powerhouse = task.goMMPassPos("Leader"),
    Special = task.goMWPassPos("Leader"),
    Defender = task.marking("First"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][APS][DHM]"
},
["MiddleMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"),
	Powerhouse = task.goMMPassPos("Leader"),
    Special = task.marking("First"),
    Defender = task.marking("Second"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][AP][SDHM]"
},
["RightMiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMMPassPos("Leader"),
	Powerhouse = task.goRMPassPos("Leader"),
    Special = task.goMWPassPos("Leader"),
    Defender = task.marking("First"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][APS][DHM]"
},

["LeftBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLMPassPos("Leader"),
	Powerhouse = task.goMMPassPos("Leader"),
    Special = task.sideBack(),
    Defender = task.marking("First"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][AP][SDHM]"
},
["MiddleBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMMPassPos("Leader"),
	Powerhouse = task.marking("Second"),
    Special = task.sideBack(),
    Defender = task.marking("First"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][A][PSDHM]"
},
["RightBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goRMPassPos("Leader"),
	Powerhouse = task.goMMPassPos("Leader"),
    Special = task.sideBack(),
    Defender = task.marking("First"),
    Hawk = task.leftBack(),
	Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][AP][SDHM]"
},
name = "Test_Advance",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
