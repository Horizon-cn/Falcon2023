--想法
--防Ning
--SideBack优先
local AdjustOurRobotNum = world:OurRobotNum()
local AdjustTheirRobotNum = world:TheirRobotNum()
local EightRobot = 8
local SevenRobot = 7
local SixRobot = 6
local FiveRobot = 5
local FourRobot = 4
local ThreeRobot = 3
---------------------------------------------------
local SupportFrontUp = 0
local SupportFrontDown = 2
local SupportMiddleUp = 3
local SupportMiddleDown = 5

local DetectBallAreaFront = function() --NotYetDone
	if ball.posY() < 0  then 
		return SupportFrontUp
	else
		return SupportFrontDown
	end
end

local DetectBallAreaMiddle = function() --NotYetDone
	if ball.posY() < 0  then 
		return SupportMiddleUp
	else
		return SupportMiddleDown
	end
end


local DivideArea = function(CornerHasBall,CornerNoBall,BackMiddleHasBall,BackMiddleNoBall,MiddleHasBall,MiddleNoBall,FrontHasBall,FrontNoBall)
	AdjustOurRobotNum = world:OurRobotNum()
	AdjustTheirRobotNum = world:TheirRobotNum()
	if (ball.posY()<-220 or ball.posY()>220) and ball.posX()<-200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return CornerHasBall
			else 
				return CornerNoBall
			end	
	elseif ball.posY()>-220 and ball.posY()<220 and ball.posX()<-200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return BackMiddleHasBall
			else 
				return BackMiddleNoBall
			end
	elseif ball.posX()>-200 and ball.posX()<200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return MiddleHasBall
			else 
				return MiddleNoBall
			end
	elseif ball.posX()>200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return FrontHasBall
			else 
				return FrontNoBall
			end
	else
		return FrontNoBall
	end
end

local SwitchBallArea = function()
	AdjustOurRobotNum = world:OurRobotNum()
	AdjustTheirRobotNum = world:TheirRobotNum()
	if	AdjustOurRobotNum == AdjustTheirRobotNum then -- 机械人数目相同
		--6或以上
		if AdjustOurRobotNum >= SixRobot  then 
			return DivideArea("HardAttack_OurMore6", --OurBall
							  "MultiDefend_OurMore6",
							  "MiddleAttack_OurMore6", --OurBall
							  "MultiDefend_OurMore6",
							  "MiddleAttack_OurMore6", --OurBall
							  "MiddleDefendBalance_OurMore6",
							  "MultiAttack_OurMore6", --OurBall
							  "MiddleAttack_OurMore6")
		--5
		elseif AdjustOurRobotNum == FiveRobot then 
			return DivideArea("HardAttack_Our5", --OurBall
							  "MultiDefend_Our5",
							  "MiddleAttack_Our5", --OurBall
							  "MultiDefend_Our5",
							  "MiddleAttack_Our5", --OurBall
							  "MiddleDefendBalance_Our5",
							  "MultiAttack_Our5", --OurBall
							  "MiddleDefendBalance_Our5")
		--4或以下
		 elseif AdjustOurRobotNum <= FourRobot then 
		 	return DivideArea("HardAttack_Ourless4", --OurBall
		 					  "MultiDefend_Ourless4",
		 					  "MiddleAttack_Ourless4", --OurBall
		 					  "MultiDefend_Ourless4",
		 					  "MiddleAttack_Ourless4", --OurBall
		 					  "MiddleDefendBalance_Ourless4",
		 					  "MiddleAttack_Ourless4", --OurBall
		 					  "MiddleDefendBalance_Ourless4")
		 else
		 	return DivideArea("HardAttack_OurMore6", --OurBall
		 					  "MultiDefend_OurMore6",
		 					  "MiddleAttack_OurMore6", --OurBall
		 					  "MultiDefend_OurMore6",
		 					  "MiddleAttack_OurMore6", --OurBall
		 					  "MiddleDefendBalance_OurMore6",
		 					  "MultiAttack_OurMore6", --OurBall
		 					  "MiddleAttack_OurMore6")
		 end
	elseif AdjustOurRobotNum ~= AdjustTheirRobotNum then -- 机械人数目不相同
		--6或以上 VS 6或以上
		if AdjustOurRobotNum >= SixRobot and AdjustTheirRobotNum >= SixRobot then 
			return DivideArea("HardAttack_OurMore6", --OurBall
							  "MultiDefend_OurMore6",
							  "MiddleAttack_OurMore6", --OurBall
							  "MultiDefend_OurMore6",
							  "MiddleAttack_OurMore6", --OurBall
							  "MiddleDefendBalance_OurMore6",
							  "MultiAttack_OurMore6", --OurBall
							  "MiddleAttack_OurMore6")
		--5 VS 6或以上
		elseif AdjustOurRobotNum == FiveRobot and AdjustTheirRobotNum >= SixRobot then 
			return DivideArea("HardAttack_Our5", --OurBall
							  "MultiDefend_Our5",
							  "MiddleAttack_Our5", --OurBall
							  "MultiDefend_Our5",
							  "MiddleAttack_Our5", --OurBall
							  "MiddleDefendBalance_Our5",
							  "MultiAttack_Our5", --OurBall
							  "MiddleAttack_Our5")
		--4或以下 VS 6或以上
		elseif AdjustOurRobotNum <= FourRobot and AdjustTheirRobotNum >= SixRobot then 
			return DivideArea("PureDefence",
							  "PureDefence",
							  "PureDefence",
							  "PureDefence",
							  "PureDefence",
							  "PureDefence",
							  "PureDefence",
							  "PureDefence")
		--6或以上 VS 4到6
		elseif AdjustOurRobotNum >= SixRobot and (AdjustTheirRobotNum <= SixRobot and  AdjustTheirRobotNum >= FourRobot) then  
			return DivideArea("HardAttack_OurMore6", --OurBall
							  "MultiDefend_OurMore6",
							  "MiddleAttack_OurMore6", --OurBall
							  "MultiDefend_OurMore6",
							  "MiddleAttack_OurMore6", --OurBall
							  "MiddleDefendBalance_OurMore6",
							  "MultiAttack_OurMore6", --OurBall
							  "MiddleAttack_OurMore6")
		--5 VS 4到6
		elseif AdjustOurRobotNum == FiveRobot and (AdjustTheirRobotNum <= SixRobot and  AdjustTheirRobotNum >= FourRobot) then 
			return DivideArea("MultiDefend_Our5", --OurBall
							  "MultiDefend_Our5",
							  "MiddleAttack_Our5", --OurBall
							  "MultiDefend_Our5",
							  "MiddleAttack_Our5", --OurBall
							  "MiddleDefendBalance_Our5",
							  "MultiAttack_Our5", --OurBall
							  "MiddleAttack_Our5")
		--4或以下 VS 4到6
		elseif AdjustOurRobotNum <= FourRobot and (AdjustTheirRobotNum <= SixRobot and  AdjustTheirRobotNum >= FourRobot) then 
			return DivideArea("PureDefence",
							  "PureDefence",
							  "PureDefence",
							  "PureDefence",
							  "PureDefence",
							  "PureDefence",
							  "PureDefence",
							  "PureDefence")
		--5或以上 VS 4或以下
		elseif AdjustOurRobotNum >= FiveRobot and AdjustTheirRobotNum <= FourRobot then  
			return DivideArea("HardAttack_OurMore6", --OurBall
							  "MultiDefend_OurMore6",
							  "MiddleAttack_OurMore6", --OurBall
							  "MultiDefend_OurMore6",
							  "MiddleAttack_OurMore6", --OurBall
							  "MiddleDefendBalance_OurMore6",
							  "MultiAttack_OurMore6", --OurBall
							  "MiddleAttack_OurMore6")
		--4或以下 VS 4或以下
		elseif AdjustOurRobotNum <= FourRobot and AdjustTheirRobotNum <= FourRobot then 
			return DivideArea("DefendFor-4or3Back",
							  "PureDefence",
							  "DefendFor-4or3Back",
							  "PureDefenceBack",
							  "AttackFor-4or3MiddleFront",
							  "DefendFor-4or3",
							  "AttackFor-4or3MiddleFront",
							  "AttackFor-4or3MiddleFront")
		else
		return DivideArea("HardAttack_OurMore6", --OurBall
						  "MultiDefend_OurMore6",
						  "MiddleAttack_OurMore6", --OurBall
						  "MultiDefend_OurMore6",
						  "MiddleAttack_OurMore6", --OurBall
						  "MiddleDefendBalance_OurMore6",
						  "MultiAttack_OurMore6", --OurBall
						  "MiddleAttack_OurMore6")
		end
	else
		return DivideArea("HardAttack_OurMore6", --OurBall
						  "MultiDefend_OurMore6",
						  "MiddleAttack_OurMore6", --OurBall
						  "MultiDefend_OurMore6",
						  "MiddleAttack_OurMore6", --OurBall
						  "MiddleDefendBalance_OurMore6",
						  "MultiAttack_OurMore6", --OurBall
						  "MiddleAttack_OurMore6")
	end
end
gPlayTable.CreatePlay{
firstState = "MiddleDefendBalance_OurMore6",
--defendhead防守圆角，可以用sideBack() 
--defendkick球门与持球人的连线
--a->p->s 优先级
--可用于危险紧急防守或边线防守
--先2multiBack 1advance 1defendhead 1markingfront 再1multiBack 可以换1defendkick
---------------------------------------------------------
["MultiDefend_OurMore6"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.multiBack(3,3),
	Defender = task.sideBack(),
	Crosser  = task.markingFront("First"),
	Breaker  = task.support("Leader",4),
	Goalie = task.goalieNew(),
	match = "[L][AMS][C][D][B]"
},

["MultiDefend_Our5"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.multiBack(3,3),
	Defender = task.sideBack(),
	Crosser  = task.markingFront("First"),
	Breaker  = task.defendHead(),
	Goalie = task.goalieNew(),
    match = "[L][AM][D][S][C][B]"
},

["MultiDefend_Ourless4"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.multiBack(3,3),
	Defender = task.task.sideBack(),--task.sideBack(),
	Crosser  = task.markingFront("First"),
	Breaker  = task.defendHead(),
	Goalie = task.goalieNew(),
    match = "[L][AM][S][D][C][B]"
},

--可用于前场进攻
["MultiAttack_OurMore6"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectBallAreaFront()),
    Middle = task.markingFront("First"),
    Breaker  = task.protectBall(),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Crosser  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][B][DC][A][S][M]"
},
-----------------------------------------------
["MultiAttack_Our5"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectBallAreaFront()),
    Middle = task.markingFront("First"),
    Breaker  = task.protectBall(),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Crosser  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][A][DC][B][S][M]"
},

["MultiAttack_Ourless4"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectBallAreaFront()),
    Middle = task.markingFront("First"),
    Breaker  = task.protectBall(),
    Special = task.multiBack(3,1),
	Defender = task.multiBack(3,2),
	Crosser  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][B][DC][A][S][M]"
},

--可用于中场半攻半防
["MiddleDefendBalance_OurMore6"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectBallAreaFront()),
    Middle = task.protectBall(), 
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  = task.multiBack(3,2),	
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DCB][A][M][S]"
},

["MiddleDefendBalance_Our5"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectBallAreaFront()),
    Middle = task.protectBall(), 
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  = task.multiBack(3,2),	
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DC][A][B][M][S]"
},


["MiddleDefendBalance_Ourless4"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectBallAreaFront()),
    Middle = task.protectBall(), 
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  = task.multiBack(3,2),	
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DCB][M][S][A]"
},

--中前进攻
["MiddleAttack_OurMore6"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectBallAreaFront()),
    Middle =  task.protectBall(), 
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  = task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DC][A][M][B][S]"
},

["MiddleAttack_Our5"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectBallAreaFront()),
    Middle =  task.protectBall(), 
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  = task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DC][A][M][B][S]"
},

["MiddleAttack_Ourless4"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectBallAreaFront()),
    Middle =  task.protectBall(), 
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  = task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DC][M][A][B][S]"
},

--适用于我方拿到球但接近我方禁区
["HardAttack_OurMore6"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4), 
    Middle = task.sideBack(), --task.marking("First"),
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  =  task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DCB][A][S][M]"
},

["HardAttack_Our5"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4), 
    Middle = task.sideBack(), --task.marking("First"),
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  =  task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DC][A][B][S][M]"
},

["HardAttack_Ourless4"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4), 
    Middle = task.sideBack(), --task.marking("First"),
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  =  task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DCB][A][S][M]"
},

------------------------------------------------------------------------
--以下为针对4车打多车的状态机
["PureDefence"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4), 
    Middle = task.sideBack(), --task.marking("First"),
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  =  task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DCB][A][S][M]"
},
------------------------------------------------------------------------
--以下为针对4车或以下打4车或以下的状态机
--4車----1Advance 1Back 1 supporter
--3車----1Advance 1Back
["DefendFor-4or3Back"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",4), 
    Middle = task.sideBack(), --task.marking("First"),
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  =  task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][D][A][CB][S][M]"
},

["AttackFor-4or3MiddleFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectBallAreaFront), 
    Middle = task.sideBack(), --task.marking("First"),
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  =  task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][D][A][CB][S][M]"
},
name = "Test_play8_Ning",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}