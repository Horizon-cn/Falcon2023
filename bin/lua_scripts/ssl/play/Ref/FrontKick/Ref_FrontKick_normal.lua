--【接球点】可根据实车情况进行调整
local SHOOT_POS = ball.antiYPos(CGeoPoint:new_local(380/1200*param.pitchLength,0/900*param.pitchWidth))

local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(40, math.pi + ball.toPointDir(SHOOT_POS())())
end

local FRONT_POS1= ball.antiYPos(CGeoPoint:new_local(350/1200*param.pitchLength,-150/900*param.pitchWidth))
local FRONT_POS2= ball.antiYPos(CGeoPoint:new_local(200/1200*param.pitchLength,-100/900*param.pitchWidth))
local FRONT_POS3= ball.antiYPos(CGeoPoint:new_local(370/1200*param.pitchLength,210/900*param.pitchWidth))

local TargetPos1= ball.antiYPos(CGeoPoint:new_local(410/1200*param.pitchLength,-100/900*param.pitchWidth))
local TargetPos2= ball.antiYPos(CGeoPoint:new_local(250/1200*param.pitchLength,0/900*param.pitchWidth))
local TargetPos3= ball.antiYPos(CGeoPoint:new_local(380/1200*param.pitchLength,150/900*param.pitchWidth))

local RECEIVE_POS = function()
  return SHOOT_POS() + Utils.Polar2Vector(40,ball.toPointDir(SHOOT_POS())())
end

local BlockPos=ball.antiYPos(CGeoPoint:new_local(430/1200*param.pitchLength,100/900*param.pitchWidth))
--【传球力度】可根据实车情况进行调整
local KICK_POWER=function()
  return 13.6*math.sqrt(ball.toPointDist(SHOOT_POS()))
end
local SupportFrontDown = 2 
local SupportFrontUp = 0
local DetectBallAreaFront = function() 
  if ball.posY() < 0  then 
    return SupportFrontDown
  else
    return SupportFrontUp
  end
end

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") < 20, 10, 180) then
        -- if ball.posY() > 0 then 
        --   return "toBall"
        -- else
        --   return "toBall"
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS,player.toPointDir(SHOOT_POS), ACC, flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(FRONT_POS3, player.toPlayerHeadDir("Assister"), ACC, flag.allow_dss + flag.dodge_ball),
    Middle   = task.goCmuRush(FRONT_POS1, player.toPlayerHeadDir("Assister"), ACC, flag.allow_dss + flag.dodge_ball),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][A][L][BC][M][S]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 20, 150, 1000) then
        return "kickBall"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS,false),
    Leader   = task.goCmuRush(RECEIVE_POS,player.toPlayerHeadDir("Assister"), ACC, STOP_DSS),
    Middle   = task.goCmuRush(BlockPos,player.toPlayerHeadDir("Assister"), ACC, STOP_DSS),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][A][L][BC][M][S]"
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.chipPass(SHOOT_POS, KICK_POWER,_,_,flag.force_kick),
    Leader   = task.goCmuRush(RECEIVE_POS,player.toPlayerHeadDir("Assister"), ACC, STOP_DSS),
    Middle   = task.goCmuRush(BlockPos,player.toPlayerHeadDir("Assister"), ACC, STOP_DSS),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][A][L][BC][M][S]"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(ball.toPlayerHeadDist("Leader") < 5, "fast", 180) then--
        return "exit"
      end
    end,
    Assister = task.support("Leader",DetectBallAreaFront),
    Leader   = task.advance(),
    Middle   = task.protectBall(),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][A][L][BC][M][S]"
  },

  name = "Ref_FrontKick_normal",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}