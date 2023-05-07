local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local distThreshold = 50
local TargetPos1  = CGeoPoint:new_local(280,200)

local Xfront = 200
local Xback = -100

local Lside = -150
local Rside = 150

local SwitchBallArea = function()
	if ball.posX() > Xfront and ball.posY() < Rside and ball.posY() > Lside then
			return "CF"
	elseif ball.posX() > Xfront then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "SW"..ballStatus
		else 
			return "SW"
		end

	elseif ball.posX() > Xback and ball.posY() > Lside and ball.posY() < Rside then
			return "CM"
	elseif ball.posX() > Xback then
			return "SM"

	elseif ball.posY() > Lside and ball.posY() < Rside then
			return "CB"
	else
			return "SB"
	end
end

-- Leader + Assister 
-- Middle
-- Goalie + Special + Defender
gPlayTable.CreatePlay{

firstState = "CM",

["SW"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Assister",0),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[LS][AD][M]"
},

["SWOurBall"] = {
	switch = SwitchBallArea,
    Leader = task.advance(),
	Assister = task.support("Assister",0),
    Middle = task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[LS][AD][M]"
},

["CF"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Assister",0),
    Middle = task.support("Middle",1),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[LS][AD][M]"
},


["SM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Assister",0),
	Middle = task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][SD][AM]"
},

["CM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Assister",0),
	Middle = task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][SD][AM]"
},


["SB"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.marking("First"),
	Middle = task.defendHead(),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][SD][AM]"
},

["CB"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.marking("First"),
	Middle = task.defendMiddle(),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][SD][AM]"
},


name = "Test_play6",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
