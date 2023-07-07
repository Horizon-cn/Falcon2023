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
	return "SixAttackFront"
end
-- Leader + Assister + Powerhouse
-- Special + Defender
-- Goalie + Middle + Hawk


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

local TargetPos1  = CGeoPoint:new_local(-410, 190)
local TargetPos2  = CGeoPoint:new_local(-171,-136)

gPlayTable.CreatePlay{

firstState = "SixAttackFront",

["SixAttackFront"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
    Special = task.support("Leader", DetectTheSupportID),
    match = "[L][S]"
},

name = "Test_NormalPass",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
