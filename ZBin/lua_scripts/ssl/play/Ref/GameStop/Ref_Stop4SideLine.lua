-- 边线球站位
-- by hjp 2021-05-19

local STOP_FLAG  = bit:_or(flag.slowly, flag.dodge_ball)
local STOP_DSS   = bit:_or(STOP_FLAG, flag.allow_dss)
local KICK_POS   = function ()
  return ball.syntYPos(CGeoPoint:new_local(ball.posX() - 59, param.pitchWidth/2-18))()
end

local MIDDLE_POS = pos.refStopAroundBall()
local KICK_DIR  = ball.antiYDir(1.57)

local OTHER_SIDE_POS = function()
  local factor = 1
  if ball.posY() > 0 then
    factor = -1
  end
  return CGeoPoint:new_local(INTER_POS():x(), factor * param.pitchWidth * 0.35)
  --return CGeoPoint:new_local(ball.posX() - 50*param.lengthRatio, 160*factor*param.widthRatio)
end

local ACC = 300

local PENALTY_THRESHOLD_DIST = 550
local MIDDLE_THRESHOLD_Y = 0.125 * param.pitchWidth --75

local topX = -(param.pitchLength/2 - param.penaltyDepth - 2 * param.playerRadius)
local sideY = param.penaltyWidth/2 + 2 * param.playerRadius
local rightTop = {
  CGeoPoint:new_local(topX, 0),
  CGeoPoint:new_local(topX, 20),
  CGeoPoint:new_local(topX, 40),
  CGeoPoint:new_local(topX, 60),
  CGeoPoint:new_local(topX, 80),
  CGeoPoint:new_local(topX, 100)
}
local leftTop = {
  CGeoPoint:new_local(topX, -0),
  CGeoPoint:new_local(topX, -20),
  CGeoPoint:new_local(topX, -40),
  CGeoPoint:new_local(topX, -60),
  CGeoPoint:new_local(topX, -80),
  CGeoPoint:new_local(topX, -100)
}
local rightSide = {
  CGeoPoint:new_local(topX - 0, sideY),
  CGeoPoint:new_local(topX - 20, sideY),
  CGeoPoint:new_local(topX - 40, sideY),
  CGeoPoint:new_local(topX - 60, sideY),
  CGeoPoint:new_local(topX - 80, sideY),
  CGeoPoint:new_local(topX - 100, sideY)
}
local leftSide = {
  CGeoPoint:new_local(topX - 0, -sideY),
  CGeoPoint:new_local(topX - 20, -sideY),
  CGeoPoint:new_local(topX - 40, -sideY),
  CGeoPoint:new_local(topX - 60, -sideY),
  CGeoPoint:new_local(topX - 80, -sideY),
  CGeoPoint:new_local(topX - 100, -sideY)
}
local standPos = leftSide
local standFunc = function(num)
  return function()
    return standPos[num]
  end
end

local function penaltyStop()
  local ballPosX = function()
    return ball.posX()
  end
  local ballPosY = function()
    return ball.posY()
  end
  if ballPosX() > topX and ballPosY() > 0 then --right top
    local ONE_POS = function()
      return CGeoPoint:new_local(topX, 0)
    end
    local TWO_POS = function()
      return CGeoPoint:new_local(topX, 20)
    end
    local THREE_POS = function()
      return CGeoPoint:new_local(topX, 40)
    end
    local FOUR_POS = function()
      return CGeoPoint:new_local(topX, 60)
    end
    local FIVE_POS = function()
      return CGeoPoint:new_local(topX, 80)
    end
    local SIX_POS = function()
      return CGeoPoint:new_local(topX, 100)
    end
  elseif ballPosX() > topX and ballPosY() < 0 then--left top
    local ONE_POS = function()
      return CGeoPoint:new_local(topX, 0)
    end
    local TWO_POS = function()
      return CGeoPoint:new_local(topX, -20)
    end
    local THREE_POS = function()
      return CGeoPoint:new_local(topX, -40)
    end
    local FOUR_POS = function()
      return CGeoPoint:new_local(topX, -60)
    end
    local FIVE_POS = function()
      return CGeoPoint:new_local(topX, -80)
    end
    local SIX_POS = function()
      return CGeoPoint:new_local(topX, -100)
    end
  elseif ballPosX() < topX and ballPosY() > 0 then--right side
    local ONE_POS = function()
      return CGeoPoint:new_local(topX - 0, sideY)
    end
    local TWO_POS = function()
      return CGeoPoint:new_local(topX - 20, sideY)
    end
    local THREE_POS = function()
      return CGeoPoint:new_local(topX - 40, sideY)
    end
    local FOUR_POS = function()
      return CGeoPoint:new_local(topX - 60, sideY)
    end
    local FIVE_POS = function()
      return CGeoPoint:new_local(topX - 80, sideY)
    end
    local SIX_POS = function()
      return CGeoPoint:new_local(topX - 100, sideY)
    end
  else --ballPosX() < topX and ballPosY() < 0 then--left side
    local ONE_POS = function()
      return CGeoPoint:new_local(topX - 0, -sideY)
    end
    local TWO_POS = function()
      return CGeoPoint:new_local(topX - 20, -sideY)
    end
    local THREE_POS = function()
      return CGeoPoint:new_local(topX - 40, -sideY)
    end
    local FOUR_POS = function()
      return CGeoPoint:new_local(topX - 60, -sideY)
    end
    local FIVE_POS = function()
      return CGeoPoint:new_local(topX - 80, -sideY)
    end
    local SIX_POS = function()
      return CGeoPoint:new_local(topX - 100, -sideY)
    end
  end

  return ONE_POS, TWO_POS, THREE_POS, FOUR_POS, FIVE_POS, SIX_POS
end

local SIDE_POS, MIDDLE_POS, INTER_POS, SIDE2_POS, INTER2_POS = pos.refStopAroundBall()
--local ONE_POS, TWO_POS, THREE_POS, FOUR_POS, FIVE_POS, SIX_POS = penaltyStop()--pos.stopPoses()

local STOP_FLAG = flag.dodge_ball
local STOP_DSS = bit:_or(STOP_FLAG, flag.allow_dss)

local gBallPosXInStop = 0
local gBallPosYInStop = 0

local OTHER_SIDE_POS1 = ball.antiYPos(CGeoPoint:new_local(-100,120))
local OTHER_SIDE_POS2 = ball.antiYPos(CGeoPoint:new_local(-100,-120))

local OTHER_SIDE_POS = function()
  local factor = 1
  if ball.posY() > 0 then
    factor = -1
  end
  return CGeoPoint:new_local(INTER_POS():x(), factor * param.pitchWidth * 0.35)
  --return CGeoPoint:new_local(ball.posX() - 50*param.lengthRatio, 160*factor*param.widthRatio)
end

gPlayTable.CreatePlay{

firstState = "start",

["start"] = {
  switch = function()
    if cond.isGameOn() then
      return "exit"
    end   
  end,
  Assister = task.goCmuRush(MIDDLE_POS, dir.playerToBall, ACC, STOP_DSS),
  --Assister = task.leftBack(),
  Special  = task.goCmuRush(KICK_POS, KICK_DIR, ACC, STOP_DSS),
  Leader   = task.goCmuRush(OTHER_SIDE_POS, dir.playerToBall, ACC, STOP_DSS),
  --Leader   = task.rightBack(),
  Middle   = task.leftBack(),
  Defender = task.rightBack(),
  Engine   = task.goLeftSupport(),
  Hawk     = task.goRightSupport(),
  Goalie   = task.goalie(),
  match    = "[SMDAL][EH]"
},

name = "Ref_Stop4SideLine",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
