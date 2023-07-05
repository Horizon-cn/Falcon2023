local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(20, -ball.antiY()*math.pi*3/4)
end

local SHOOT_POS = function()
  return ball.pos()+Utils.Polar2Vector(400,ball.antiY()*math.pi/6)
end

local RECEIVE_POS = function()
  return SHOOT_POS() + Utils.Polar2Vector(20,ball.toPointDir(SHOOT_POS())()+math.pi)
end

local ASSIST_POS = function()
  return SHOOT_POS()+Utils.Polar2Vector(140,ball.antiY()*math.pi/4)
end

local KICK_POWER = function()
  local kickPower = 13.6*math.sqrt(ball.toPointDist(SHOOT_POS()))
  if kickPower > 450 then
    return 450
  else
    return kickPower
  end
end

local BlockPos=ball.antiYPos(CGeoPoint:new_local(430/1200*param.pitchLength,-100/900*param.pitchWidth))

local SupportFrontDown = 5 
local SupportFrontUp = 3
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
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS,player.toPointDir(SHOOT_POS),_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(RECEIVE_POS, player.toPointDir(SHOOT_POS), ACC, STOP_DSS),
    Middle   = task.goCmuRush(ASSIST_POS, player.toPlayerHeadDir("Leader"), ACC, STOP_DSS),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][M][S]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 20, 70, 500) then
        return "kickBall"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS),
    Leader   = task.goCmuRush(RECEIVE_POS, player.toPlayerHeadDir("Assister"), ACC, STOP_DSS),
    Middle   = task.goCmuRush(ASSIST_POS, player.toPlayerHeadDir("Leader"), ACC, STOP_DSS),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][M][S]"
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.chipPass(SHOOT_POS, KICK_POWER),
    Leader   = task.goCmuRush(RECEIVE_POS, player.toPlayerHeadDir("Assister"), ACC, STOP_DSS),
    Middle   = task.goCmuRush(ASSIST_POS, player.toPlayerHeadDir("Leader"), ACC, STOP_DSS),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][M][S]"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(ball.toPlayerHeadDist("Leader") < 5, "fast", 180) then
        return "shootBall"
      end
    end,
    Assister = task.defendMiddle(),
    Leader   = task.advance(),
    Middle   = task.support("Leader",DetectBallAreaFront),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][M][S]"
  },

["shootBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Leader"), 3, 150) then
        return "exit"
      end
    end,
    Assister = task.defendMiddle(),
    Leader   = task.advance(),
    Middle   = task.support("Leader",DetectBallAreaFront),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][M][S]"
  },

  name = "Ref_BackPush_normal_chip",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}