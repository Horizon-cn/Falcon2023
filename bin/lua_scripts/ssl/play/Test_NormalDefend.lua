-- 针对22年 线上赛防守代码
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
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.defendMiddle(), 
    Powerhouse = task.multiBack(3,3),
    Defender = task.goMMPassPos("Leader"),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},

["MiddleFront"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goLWPassPos("Leader"),
    Assister = task.defendMiddle(), 
    Powerhouse = task.multiBack(3,3),
    Defender = task.goRWPassPos("Leader"),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},

["RightFront"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.defendMiddle(), 
    Powerhouse = task.multiBack(3,3),
    Defender = task.goLWPassPos("Leader"),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},

["LeftMiddleFront"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.defendMiddle(), 
    Powerhouse = task.multiBack(3,3),
    Defender = task.goLWPassPos("Leader"),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},

["MiddleMiddleFront"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.defendMiddle(), 
    Powerhouse = task.multiBack(3,3),
    Defender = task.goLWPassPos("Leader"),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},
["RightMiddleFront"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.defendMiddle(), 
    Powerhouse = task.multiBack(3,3),
    Defender = task.goRWPassPos("Leader"),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},

["LeftMiddleBack"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.goCmuRush(CGeoPoint:new_local(-430,0),_,_,flag.allow_dss),
    Powerhouse = task.goCmuRush(CGeoPoint:new_local(-460,140),_,_,flag.allow_dss),
    Defender = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},
["MiddleMiddleBack"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.goCmuRush(CGeoPoint:new_local(-460,-140),_,_,flag.allow_dss),
    Powerhouse = task.goCmuRush(CGeoPoint:new_local(-460,140),_,_,flag.allow_dss),
    Defender = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},

["RightMiddleBack"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.goCmuRush(CGeoPoint:new_local(-430,0),_,_,flag.allow_dss),
    Powerhouse = task.goCmuRush(CGeoPoint:new_local(-460,-140),_,_,flag.allow_dss),
    Defender = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},

["LeftBack"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.goCmuRush(CGeoPoint:new_local(-430,0),_,_,flag.allow_dss),
    Powerhouse = task.goCmuRush(CGeoPoint:new_local(-460,140),_,_,flag.allow_dss),
    Defender = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},
["MiddleBack"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.goCmuRush(CGeoPoint:new_local(-460,-140),_,_,flag.allow_dss),
    Powerhouse = task.goCmuRush(CGeoPoint:new_local(-460,140),_,_,flag.allow_dss),
    Defender = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},
["RightBack"] = {
    switch = SwitchBallArea,
    --Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.goCmuRush(CGeoPoint:new_local(-430,0),_,_,flag.allow_dss),
    Powerhouse = task.goCmuRush(CGeoPoint:new_local(-460,-140),_,_,flag.allow_dss),
    Defender = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[L][HM][SAPD]"
},
name = "Test_NormalDefend",
applicable ={
    exp = "a",
    a = true
},
attribute = "attack",
timeout = 99999
}
