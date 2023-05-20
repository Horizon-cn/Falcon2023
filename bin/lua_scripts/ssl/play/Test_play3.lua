local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local distThreshold = 50
local TargetPos1  = CGeoPoint:new_local(280,200)

local Xfront = 100
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
	elseif ball.posX() > Xfront and ball.posY() < Lside then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "LW"..ballStatus
		else 
			return "LW"
		end
	elseif ball.posX() > Xfront then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "RW"..ballStatus
		else 
			return "RW"
		end
	elseif ball.posX() > Xmid and ball.posY() > Lside and ball.posY() < Rside then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "CM"..ballStatus
		else 
			return "CM"
		end
	elseif ball.posX() > Xmid and ball.posY() < Lside then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "LM"..ballStatus
		else 
			return "LM"
		end	
	elseif ball.posX() > Xmid then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "RM"..ballStatus
		else 
			return "RM"
		end

	elseif ball.posX() > Xback and ball.posY() > Lside and ball.posY() < Rside then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "CDM"..ballStatus
		else 
			return "CDM"
		end
	elseif ball.posX() > Xback and ball.posY() < Lside then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "LDM"..ballStatus
		else 
			return "LDM"
		end
	elseif ball.posX() > Xback then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "RDM"..ballStatus
		else 
			return "RDM"
		end

	elseif ball.posY() > Lside and ball.posY() < Rside then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "CB"..ballStatus
		else 
			return "CB"
		end
	elseif ball.posY() < Lside then
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "LB"..ballStatus
		else 
			return "LB"
		end
	else
		ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
		if ballStatus == "OurBall" then
			return "RB"..ballStatus
		else 
			return "RB"
		end
	end
end

-- Leader + Assister 
-- Middle
-- Goalie + Special + Defender
gPlayTable.CreatePlay{

firstState = "CM",

--front
["LW"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},

["LWOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLMPassPos("Leader"),
    Middle = task.goMWPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

["CF"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},

["CFOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goRWPassPos("Leader"),
    Middle = task.goLWPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

["RW"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},

["RWOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"),
    Middle = task.goRMPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

-- mid
["LM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},

["LMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLWPassPos("Leader"),
    Middle = task.goMMPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

["CM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},

["CMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goRWPassPos("Leader"),
    Middle = task.goLWPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

["RM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},

["RMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goRWPassPos("Leader"),
    Middle = task.goMMPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

--middldDefence

["LDM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},

["LDMOurBall"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMMPassPos("Leader"),
    Middle = task.goLMPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

["CDM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},

["CDMOurBall"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goRMPassPos("Leader"),
    Middle = task.goLMPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

["RDM"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},

["RDMOurBall"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMMPassPos("Leader"),
    Middle = task.goRMPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

--back
["LB"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},
["LBOurBall"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLMPassPos("Leader"),
    Middle = task.goMMPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

["CB"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},
["CBOurBall"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goLMPassPos("Leader"),
    Middle = task.goRMPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},

["RB"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.markingFront("First"),
    Middle = task.markingFront("Second"), --task.marking("First"),
    match = "[L][A][M]"
},
["RBOurBall"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goRMPassPos("Leader"),
    Middle = task.goMMPassPos("Leader"), --task.marking("First"),
    match = "[L][A][M]"
},


name = "Test_play3",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
