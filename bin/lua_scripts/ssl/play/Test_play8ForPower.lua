--jlc 2023.7.4 advocate support

local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local Xfront = 300
local Xmid = 0
local Xback = -300

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
	Assister = task.support("Leader",1),
    Middle = task.support("Leader",4), --task.marking("First"),
    Special = task.markingFront("First"),
	Defender = task.leftBack(),
	Breaker = task.rightBack(),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
    match = "[L][A][DB][C][S][M]"
},

["SWOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
    Middle = task.support("Leader",4), --task.marking("First"),
    Special = task.markingFront("First"),
	Defender = task.leftBack(),
	Breaker = task.rightBack(),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
	match = "[L][A][DB][C][M][S]"
},

["CF"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",3),
    Middle = task.support("Leader",5), --task.marking("First"),
    Special = task.markingFront("First"),
	Defender = task.leftBack(),
	Breaker = task.rightBack(),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
	match = "[L][DB][A][C][S][M]"

},

["CFOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
    Middle = task.support("Leader",2), --task.marking("First"),
    Special = task.defendMiddle(),
	Defender = task.leftBack(),
	Breaker = task.rightBack(),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
	match = "[L][DB][A][C][S][M]"
},

-- mid
["SM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4),
	Middle = task.markingFront("First"),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Breaker = task.multiBack(3,3),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
    match = "[L][SD][A][M][B][C]"
},

["SMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4),
	Middle = task.markingFront("First"),
    Special = task.defendMiddle(),
	Defender = task.leftBack(),
	Breaker = task.rightBack(),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
    match = "[L][SD][A][B][M][C]"
},

["CM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",1),
	Middle = task.markingFront("First"),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Breaker = task.multiBack(3,3),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
    match = "[L][SD][A][B][M][C]"
},

["CMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4),
	Middle = task.markingFront("First"),
    Special = task.defendMiddle(),
	Defender = task.leftBack(),
	Breaker = task.rightBack(),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
    match = "[L][SD][A][B][C][M]"
},

--middldDefence

["CDM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4),
	Middle = task.markingFront("First"),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Breaker = task.multiBack(3,3),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
    match = "[L][SD][A][B][M][C]"
},

["CDMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4),
	Middle = task.markingFront("First"),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Breaker = task.multiBack(3,3),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
    match = "[L][SD][A][B][C][M]"
},

["SDM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4),
	Middle = task.markingFront("First"),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Breaker = task.multiBack(3,3),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
    match = "[L][SDB][A][M][C]"
},

["SDMOurBall"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4),
	Middle = task.markingFront("First"),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Breaker = task.multiBack(3,3),
	Crosser = task.protectBall(),
	Goalie = task.goalieNew(),
    match = "[L][SDB][A][C][M]"
},

--back
["SB"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4),
	Middle = task.markingFront("First"),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Breaker = task.multiBack(3,3),
	Crosser = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][SDB][A][M][C]"
},

["CB"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",5),
	Middle = task.markingFront("First"),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Breaker = task.multiBack(3,3),
	Crosser = task.markingFront("Second"),
	Goalie = task.goalieNew(),
    match = "[L][SDB][A][M][C]"
},


name = "Test_play8ForPower",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
