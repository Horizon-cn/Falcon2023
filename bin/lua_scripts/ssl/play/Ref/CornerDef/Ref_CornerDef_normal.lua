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

local DefendMiddlePos = CGeoPoint:new_local(-470/1200*param.pitchLength,20)
local DefendMiddlePos_2 = CGeoPoint:new_local(-470/1200*param.pitchLength,-20)

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader   = task.defendMiddle(),
  Assister = task.goCmuRush(DefendMiddlePos_2,player.toPointDir(SHOOT_POS),ACC,flag.allow_dss + flag.dodge_ball),
  Middle   = task.goCmuRush(DefendMiddlePos,player.toPointDir(SHOOT_POS),ACC,flag.allow_dss + flag.dodge_ball),
  Special  = task.support("Leader",DetectTheSupportID), 
  Defender = task.sideBack(),
  Crosser  = task.singleBack(),
  Breaker  = task.sideBackUltra(),
  Goalie   = task.goalieNew(),
  --match    = "[L][DC][S][M][A][B]"
  match    = "[L][M][D][S][A][C][B]"
},
  name = "Ref_CornerDef_normal",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}