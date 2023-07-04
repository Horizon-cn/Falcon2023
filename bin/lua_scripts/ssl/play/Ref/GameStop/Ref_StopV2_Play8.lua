local SwitchBallArea = function()
  if cond.isGameOn() then
    return "exit"
  elseif ball.posX() > 480 and math.abs(ball.posY()) > 300 then --我方CornerKick
    return "CornerKickStop"
  elseif ball.posX() > 100 then --我方FrontKick
    return "FrontKickStop"
  elseif ball.posX() > -100 then --半攻半防
    return "MiddleStop"
  elseif ball.posX() < -300 and math.abs(ball.posY()) > 120  then 
    return "CornerDefendStop"
  elseif ball.posX() < -300 and math.abs(ball.posY()) < 120 then
    return "BackDefendStop"
  else
    return "BackDefendStop"
  end
end

--CornerKickStop FrontKickStop
------------------------
local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(60, ball.syntY(0.5 * math.pi))
end
local KICK_DIR  = ball.antiYDir(1.57)
local FRONT_POS1= ball.antiYPos(CGeoPoint:new_local(350/1200*param.pitchLength,-150/900*param.pitchWidth))
local FRONT_POS2= ball.antiYPos(CGeoPoint:new_local(260/1200*param.pitchLength,0/900*param.pitchWidth))
local FRONT_POS3= ball.antiYPos(CGeoPoint:new_local(370/1200*param.pitchLength,210/900*param.pitchWidth))
local ACC=500;
------------------------

--MiddleStop
------------------------
local SupportFrontDown = 2 
local SupportFrontUp = 0
local DetectBallAreaFront = function() 
  if ball.posY() < 0  then 
    return SupportFrontDown
  else
    return SupportFrontUp
  end
end
------------------------



gPlayTable.CreatePlay{
  firstState = "BackDefendStop",
["CornerKickStop"]= {
  switch   = SwitchBallArea,
  Assister = task.goCmuRush(WAIT_BALL_POS, KICK_DIR, ACC, STOP_DSS),
  Leader   = task.goCmuRush(FRONT_POS1, _, ACC, STOP_DSS),
  Middle   = task.goCmuRush(FRONT_POS2, _, ACC, STOP_DSS),
  Special  = task.goCmuRush(FRONT_POS3, _, ACC, STOP_DSS),
  Defender = task.multiBack(3,1),
  Breaker  = task.multiBack(3,2),
  Crosser  = task.multiBack(3,3),
  Goalie   = task.goalieNew(),
  match = "[D][B][A][C][S][L][M]"
},

["FrontKickStop"]= {
  switch   = SwitchBallArea,
  Assister = task.goCmuRush(WAIT_BALL_POS, KICK_DIR, ACC, STOP_DSS),
  Leader   = task.goCmuRush(FRONT_POS1, _, ACC, STOP_DSS),
  Middle   = task.goCmuRush(FRONT_POS2, _, ACC, STOP_DSS),
  Special  = task.goCmuRush(FRONT_POS3, _, ACC, STOP_DSS),
  Defender = task.multiBack(3,1),
  Breaker  = task.multiBack(3,2),
  Crosser  = task.multiBack(3,3),
  Goalie   = task.goalieNew(),
  match    = "[D][B][A][C][S][L][M]"
},

--接normalPlay
["MiddleStop"]= {
  switch   = SwitchBallArea,
  Leader   = task.defendKick(),
  Assister = task.markingFront("First"),
  Middle   = task.stop(),
  Special  = task.support("Leader",DetectBallAreaFront), 
  Defender = task.multiBack(3,1),
  Crosser  = task.multiBack(3,2),
  Breaker  = task.multiBack(3,3),
  Goalie   = task.goalieNew(),
  match    = " "
},

["CornerDefendStop"]= {
    --1defendKick 1or2個multiBack 1個sideBack 1個sideBack_Ultra 1個 
  switch   = SwitchBallArea,
  Leader   =task.stop(),
  Assister =task.stop(),
  Middle   = task.stop(),
  Special  = task.stop(),
  Defender = task.stop(),
  Crosser  = task.stop(),
  Breaker  = task.stop(),
  Goalie   = task.stop(),
  match    = "[LAMSDCB]"
},  

["BackDefendStop"]= {
  switch   = SwitchBallArea,
  Leader   =task.stop(),
  Assister =task.stop(),
  Middle   = task.stop(),
  Special  = task.stop(),
  Defender = task.stop(),
  Crosser  = task.stop(),
  Breaker  = task.stop(),
  Goalie   = task.stop(),
  match    = "[LAMSDCB]"
},  

  name = "Ref_StopV2_Play8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}