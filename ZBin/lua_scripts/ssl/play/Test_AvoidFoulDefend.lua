-- 针对22年 线上赛避免犯规的极端代码
-- 
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
    return "FUCK"
end

-- Leader + Assister + Powerhouse
-- Special + Defender
-- Goalie + Middle + Hawk
gPlayTable.CreatePlay{

firstState = "FUCK",

["FUCK"] = {
    switch = SwitchBallArea,
    Leader = task.advance(),
    Hawk = task.multiBack(5,1),
    Middle = task.multiBack(5,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.multiBack(5,3),
    Powerhouse = task.multiBack(5,4),
    Defender = task.multiBack(5,5),
    Goalie = task.goalieNew(),
    match = "[L][HM][S][APD]"
},

name = "Test_AvoidFoulDefend",
applicable ={
    exp = "a",
    a = true
},
attribute = "attack",
timeout = 99999
}