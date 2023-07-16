-- 正常进攻 Strong

-- 6 VS 6 : 前场：G + Advance + 2Back + Sup + Back + Protect + Mark
--       czm前场：G + Advance + 2Back + Sup + Protect + Back + Mark
--          后场：G + Advance + 2Back + Sup + Back + Mark + Protect     -- 如果Marking犯规多，换成SideBack

-- 5 VS 7+ :     G + Advance + 3Back
-- 5 VS 7- : 同6V6 
-- 4-: G + chaseNew + 2Back

local AdjustOurRobotNum = world:OurRobotNum()
local AdjustTheirRobotNum = world:TheirRobotNum()
local EightRobot = 8
local SevenRobot = 7
local SixRobot = 6
local FiveRobot = 5
local FourRobot = 4
local ThreeRobot = 3
---------------------------------------------------

local DetectTheSupportID = function() 
    if ball.posX() > 200 and ball.posY() < -120 then  -- 在0号区域
        return 2  -- 往2号区域打
    elseif ball.posX() > 200 and ball.posY() < 120 then -- 在1号区域
        if ball.posX() > 0 then
            return 2
        else 
            return 0
        end
    elseif ball.posX() > 200 and ball.posY() >= 120 then -- 在2号区域
        return 0 -- 往0号打
    elseif ball.posX() > -200 and ball.posY() < -120 then -- 在3号区域
        return 0 -- 往0号打
    elseif ball.posX() > -200 and ball.posY() < 120 then -- 在4号区域
        return 1 -- 往1号打
    elseif ball.posX() > -200 and ball.posY() >= 120 then -- 在5号区域
        return 2 -- 往2号打
    else
        return 4 -- 往4号打
    end
end

local DivideArea = function(Front, Back)
    if (ball.posX() > 0) then
        return Front
    else 
        return Back
    end
end

local SwitchBallArea = function()
	AdjustOurRobotNum = world:OurRobotNum()
	AdjustTheirRobotNum = world:TheirRobotNum()
    if AdjustOurRobotNum >= EightRobot then
        return DivideArea("SixAttackFront8", "SixAttackBack8")
    elseif AdjustOurRobotNum >= SixRobot then
        return DivideArea("SixAttackFront6", "SixAttackFront6")
    elseif AdjustOurRobotNum == FiveRobot then
        if AdjustTheirRobotNum >= 7 then
            return DivideArea("PureDefenceFront", "PureDefenceBack")
        else
            return DivideArea("SixAttackFront", "SixAttackBack")
        end
    else
        return DivideArea("ChaseRushFront", "ChaseRushBack")
    end
end

gPlayTable.CreatePlay{
firstState = "SixAttackFront",

-- 6 VS 6 : 前场：G + Advance + 2Back + Sup + DefendMiddle + Protect + Mark
--          后场：G + Advance + 2Back + Sup + Back + Mark + Protect     -- 如果Marking犯规多，换成SideBack

-- 5 VS 7+ :     G + Advance + 2Back + DefendMiddle
-- 5 VS 7- : 同6V6 
-- 4-: G + chaseNew + 2Back
---------------------------------------------------------
-- task.goCmuRush(MIDDLE_POS_1, player.toPointDir(ball.pos())),
-- player.toShootOrRobot(role)
-- task.advance(),
-- task.chaseNew()
["SixAttackFront8"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.leftBack(),
    Middle = task.rightBack(),
    Special = task.support("Leader", DetectTheSupportID),
    Defender = task.defendMiddle(),
	Crosser = task.marking("First"), -- task.protectBall(),
	Breaker  = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][AMBD][S][C]"
},

["SixAttackBack8"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.leftBack(), -- task.multiBack(3,1),
    Middle = task.rightBack(), -- task.multiBack(3,2),
    Special = task.support("Leader", DetectTheSupportID),
    Defender = task.helperBack(), -- task.multiBack(3,3),
	Crosser = task.marking("First"), -- task.protectBall(),
	Breaker  = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][AMBD][S][C]"
},
["SixAttackFront6"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.leftBack(),
    Middle = task.rightBack(),
    Special = task.support("Leader", DetectTheSupportID),
    Defender = task.defendMiddle(),
	Crosser = task.marking("First"), -- task.protectBall(),
	Goalie = task.goalieNew(),
    match = "[L][AMD][S][C]"
},

["SixAttackBack6"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.leftBack(), -- task.multiBack(3,1),
    Middle = task.rightBack(), -- task.multiBack(3,2),
    Special = task.support("Leader", DetectTheSupportID),
    Defender = task.helperBack(), -- task.multiBack(3,3),
	Crosser = task.marking("First"), -- task.protectBall(),
	Breaker  = task.sideBack(),
	Goalie = task.goalieNew(),
    match = "[L][AMB][S][C]"
},
["SixAttackFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.leftBack(),
    Middle = task.rightBack(),
    Special = task.support("Leader", DetectTheSupportID),
    Defender = task.defendMiddle(),
	Goalie = task.goalieNew(),
    match = "[L][AMD][S]"
},

["SixAttackBack"] = {
    switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.leftBack(), -- task.multiBack(3,1),
    Middle = task.rightBack(), -- task.multiBack(3,2),
    Special = task.support("Leader", DetectTheSupportID),
    Defender = task.helperBack(), -- task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][AMD][S]"
},

["ChaseRushFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.leftBack(),
    Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][AM]"
},
["ChaseRushBack"] = {
	switch = SwitchBallArea,
	Leader = task.chaseNew(),
	Assister = task.leftBack(),
    Middle = task.rightBack(),
	Goalie = task.goalieNew(),
    match = "[L][AM]"
},

["PureDefenceFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectTheSupportID), 
    Middle = task.sideBack(), 
    Special = task.marking("First"), -- task.protectBall(),
	Defender = task.leftBack(),
	Crosser  =  task.rightBack(),
	Breaker  = task.defendMiddle(),
	Goalie = task.goalieNew(),
    match = "[L][DCB][A][S][M]"
},

["PureDefenceBack"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",DetectTheSupportID), 
    Middle = task.sideBack(), 
    Special = task.marking("First"), -- task.protectBall(),
	Defender = task.leftBack(),
	Crosser  =  task.rightBack(),
	Breaker  = task.marking("Second"),
	Goalie = task.goalieNew(),
    match = "[L][DCM][A][S][M]"
},
name = "Nor_8_Simple",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}