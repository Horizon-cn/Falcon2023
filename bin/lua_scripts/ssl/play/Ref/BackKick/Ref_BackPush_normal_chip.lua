local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(60, ball.syntY(0.5 * math.pi))
end

local SHOOT_POS = function()
	if  ball.posX() > -480/1200*param.pitchLength and math.abs(ball.posY())>120/900*param.pitchWidth then
    return ball.antiYPos(CGeoPoint:new_local(200/1200*param.pitchLength,-240/900*param.pitchWidth))
  elseif ball.posX() < -100/1200*param.pitchLength and math.abs(ball.posY())<240/900*param.pitchWidth then
    return ball.antiYPos(CGeoPoint:new_local(300/1200*param.pitchLength,240/900*param.pitchWidth))
  elseif math.abs(ball.posY())>240/900*param.pitchWidth then
    return ball.antiYPos(CGeoPoint:new_local(150/1200*param.pitchLength,240/900*param.pitchWidth))
end

local RECEIVE_POS = function()
  return SHOOT_POS() + Utils.Polar2Vector(20,ball.toPointDir(SHOOT_POS())()+ball.antiY(0.5*math.pi))
end

local ASSIST_POS = function()
  if  ball.posX() > -480/1200*param.pitchLength and math.abs(ball.posY())>120/900*param.pitchWidth then
    return ball.syntYPos(CGeoPoint:new_local(350/1200*param.pitchLength,-240/900*param.pitchWidth))
  else
    return ball.antiYPos(CGeoPoint:new_local(350/1200*param.pitchLength,-240/900*param.pitchWidth))
end

local KICK_POWER = function()
  local kickPower = 13.6*math.sqrt(ball.toPointDist(SHOOT_POS()))
  if kickPower > 450 then
    return 450
  else
    return kickPower
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
    Assister = task.goCmuRush(WAIT_BALL_POS,_,_,flag.allow_dss + flag.dodge_ball),
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
    Leader   = task.goCmuRush(RECEIVE_POS, player.toPointDir(SHOOT_POS), ACC, STOP_DSS),
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
    Leader   = task.goCmuRush(RECEIVE_POS, player.toPointDir(SHOOT_POS), ACC, STOP_DSS),
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
    Assister = task.goCmuRush(BlockPos, player.toPlayerHeadDir("Assister"), ACC, STOP_DSS),
    Leader   = task.advance(),
    Middle   = task.support("Leader"),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][M][S]"
  },

["shootBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Special"), 3, 150) then
        return "exit"
      end
    end,
    Assister = task.goCmuRush(BlockPos, player.toPlayerHeadDir("Assister"), ACC, STOP_DSS),
    Leader   = task.advance(),
    Middle   = task.support("Leader"),
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