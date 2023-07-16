--jlc 2023.7.3 for Test: 6 VS 6

local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local Xfront = 200
local Xmid = -100
local Xback = -250

local Lside = -100
local Rside = 100

local SwitchBallArea = function()
	if ball.posX() > Xfront and ball.posY() < Rside and ball.posY() > Lside then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "CF"..ballStatus
		else 
			return "CF"
		end
	elseif ball.posX() > Xfront then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "SW"..ballStatus
		else 
			return "SW"
		end

	elseif ball.posX() > Xmid and ball.posY() > Lside and ball.posY() < Rside then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "CM"..ballStatus
		else 
			return "CM"
		end
	elseif ball.posX() > Xmid then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "SM"..ballStatus
		else 
			return "SM"
		end

	elseif ball.posX() > Xback and ball.posY() > Lside and ball.posY() < Rside then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "CDM"..ballStatus
		else 
			return "CDM"
		end
	elseif ball.posX() > Xback then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "SDM"..ballStatus
		else 
			return "SDM"
		end

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

--front
["SW"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.singleBack(),
	Defender = task.defendMiddle(),
	Goalie = task.goalieNew(),
    match = "[L][DS][M][A]"
},

["SWOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.singleBack(),
	Defender = task.defendMiddle(),
	Goalie = task.goalieNew(),
    match = "[L][DS][A][M]"
},

["CF"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.singleBack(),
	Defender = task.defendMiddle(),
	Goalie = task.goalieNew(),
    match = "[L][DS][M][A]"
},

["CFOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.singleBack(),
	Defender = task.defendMiddle(),
	Goalie = task.goalieNew(),
    match = "[L][DS][M][A]"
},

-- mid
["SM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DS][M][A]"
},

["SMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DS][M][A]"
},

["CM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DS][A][M]"
},

["CMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",2),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DS][A][M]"
},

--middldDefence

["CDM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
    Middle = task.markingFront("First"), --task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DS][A][M]"
},

["CDMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DS][A][M]"
},

["SDM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
    Middle = task.markingFront("First"), --task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DS][A][M]"
},

["SDMOurBall"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
    Middle = task.protectBall(), --task.marking("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DS][A][M]"
},

--back
["SB"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.markingFront("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DS][A][M]"
},

["CB"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.markingFront("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DS][A][M]"
},


name = "Nor_6",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
