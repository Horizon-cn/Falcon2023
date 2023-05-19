local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local distThreshold = 50
local TargetPos1  = CGeoPoint:new_local(280,200)

local Xfront = 200
local Xmid = -100
local Xback = -250

local Lside = -150
local Rside = 150

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
	Assister = task.support("Leader",0),
    Middle = task.support("Leader",1), --task.marking("First"),
    Special = task.defendMiddle(),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DAS][M]"
},

["SWOurBall"] = {
	switch = SwitchBallArea,
    Leader = task.advance(),
	Assister = task.support("Leader",0),
    Middle = task.support("Leader",1),
    Special = task.support("Leader",2),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DAS][M]"
},

["CF"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
    Middle = task.support("Leader",1),
    Special = task.defendMiddle(),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DAS][M]"
},

["CFOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
    Middle = task.support("Leader",1),
    Special = task.support("Leader",2),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DAS][M]"
},

-- mid
["SM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.support("Leader",1),
    Special = task.markingFront("First"),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DA][SM]"
},

["SMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.support("Leader",1),
    Special = task.support("Leader",2),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DA][MS]"
},

["CM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.support("Leader",1),
    Special = task.markingFront("First"),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DA][SM]"
},

["CMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.support("Leader",1),
    Special = task.support("Leader",2),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DA][MS]"
},

--middldDefence

["CDM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.support("Leader",1),
    Special = task.markingFront("First"),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DA][SM]"
},

["CDMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.support("Leader",1),
    Special = task.markingFront("First"),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DA][MS]"
},

["SDM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.support("Leader",1),
    Special = task.defendHead(),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DA][MS]"
},

["SDMOurBall"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.support("Leader",1),
    Special = task.markingFront("First"),
	Defender = task.singleBack(),
	Goalie = task.goalieNew(),
    match = "[L][DA][SM]"
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
    match = "[L][DA][SM]"
},

["CB"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
	Middle = task.markingFront("First"),
    Special = task.leftBack(),
	Defender = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][DA][SM]"
},


name = "Test_play6",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
