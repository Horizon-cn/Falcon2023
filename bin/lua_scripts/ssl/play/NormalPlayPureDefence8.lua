
local MIDDLE_POS_1   = CGeoPoint:new_local(-470,-130)
local MIDDLE_POS_2   = CGeoPoint:new_local(-470,130)
local MIDDLE_POS_3   = CGeoPoint:new_local(-462,0)
local AdjustOurRobotNum = world:OurRobotNum()
local AdjustTheirRobotNum = world:TheirRobotNum()
local EightRobot = 8
local SevenRobot = 7
local SixRobot = 6
local FiveRobot = 5
local FourRobot = 4
local ThreeRobot = 3

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
    if AdjustOurRobotNum >= SevenRobot then
        return DivideArea("PureDefence7Front", "PureDefence7Back")
	elseif AdjustOurRobotNum == SixRobot then
		return "PureDefence6"
    elseif AdjustOurRobotNum <= FiveRobot then
        return "PureDefence5"
    end
end


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
gPlayTable.CreatePlay{

firstState = "PureDefence7Front",

["PureDefence7Front"] = {
	switch = SwitchBallArea,
	Leader   = task.support("Special", DetectTheSupportID),
	Assister = task.goCmuRush(MIDDLE_POS_1, player.toBallDir("Assister")),
    Special  = task.advance(),
	Defender = task.leftBack(),
	Breaker  = task.rightBack(),
	Crosser  = task.defendMiddle(),
    Middle   = task.goCmuRush(MIDDLE_POS_2, player.toBallDir("Middle")),
	Goalie   = task.goalieNew(),
    match = "[S][DBMAC][L]"
},
["PureDefence7Back"] = {
	switch = SwitchBallArea,
	Leader   = task.support("Special", DetectTheSupportID),
	Assister = task.goCmuRush(MIDDLE_POS_1, player.toBallDir("Assister")),
    Special  = task.advance(),
	Defender = task.leftBack(),
	Breaker  = task.rightBack(),
	Crosser  = task.goCmuRush(MIDDLE_POS_3, player.toBallDir("Crosser")),
    Middle   = task.goCmuRush(MIDDLE_POS_2, player.toBallDir("Middle")),
	Goalie   = task.goalieNew(),
    match = "[S][DBMAC][L]"
},

["PureDefence6"] = {
    switch = SwitchBallArea,
	Assister = task.sideBack(),
    Special  = task.advance(),
	Defender = task.leftBack(),
	Breaker  = task.rightBack(),
	Crosser  = task.support("Special", DetectTheSupportID),
	Goalie   = task.goalieNew(),
    match = "[S][DCA][B]"
},
["PureDefence5"] = {
    switch = SwitchBallArea,
	Assister = task.sideBack(),
    Special  = task.advance(),
	Defender = task.leftBack(),
	Breaker  = task.rightBack(),
	Goalie   = task.goalieNew(),
    match = "[S][DBA]"
},
name = "NormalPlayPureDefence8",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
