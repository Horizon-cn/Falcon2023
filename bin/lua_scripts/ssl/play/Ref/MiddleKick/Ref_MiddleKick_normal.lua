local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end

local RECEIVE_POS = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local(550/1200*param.pitchLength,120/900*param.pitchWidth))()
  else
    return ball.syntYPos(CGeoPoint:new_local(560/1200*param.pitchLength,0/900*param.pitchWidth))()
  end
end
local BLOCK_POS = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local(ball.posX(),350/900*param.pitchWidth))()
  else
    return ball.syntYPos(CGeoPoint:new_local(ball.posX(),200/900*param.pitchWidth))()
  end
end
local BARYCENTER = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local((550+ball.posX())/2/1200*param.pitchLength,235/900*param.pitchWidth))()
  else
    return ball.syntYPos(CGeoPoint:new_local((560+ball.posX())/2/1200*param.pitchLength,250/900*param.pitchWidth))() 
  end
end
local BLOCK_POS2 = function()
  return ball.syntYPos(CGeoPoint:new_local(430/1200*param.pitchLength,0/900*param.pitchWidth))()
end
local RECEIVE_POS2 = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local(250/1200*param.pitchLength,60/900*param.pitchWidth))()
  else
    return ball.syntYPos(CGeoPoint:new_local(170/1200*param.pitchLength,80/900*param.pitchWidth))()
  end
end
local SHOOT_POS = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local(510/1200*param.pitchLength,70/900*param.pitchWidth))()
  else
    return ball.syntYPos(CGeoPoint:new_local(490/1200*param.pitchLength,80/900*param.pitchWidth))()
  end
end
local KICK_POWER=function()
  return 13.6*math.sqrt(ball.toPointDist(RECEIVE_POS2()))
end
local shootPower = 400
gPlayTable.CreatePlay{

  firstState = "get",

  ["get"] = {
    switch = function()
      if bufcnt(player.toTargetDist("Special") < 20 or player.toTargetDist("Leader") < 20,"normal",500) then
        return "move"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS,_,_,flag.allow_dss + flag.dodge_ball),
    Special  = task.goCmuRush(BLOCK_POS,player.toBallDir,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(BARYCENTER,player.toBallDir,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.stop(),
    Defender = task.stop(),
    Breaker  = task.stop(),
    Crosser  = task.stop(),   
    -- Middle   = task.multiBack(4,1),
    -- Defender = task.multiBack(4,2),
    -- Breaker  = task.multiBack(4,3),
    -- Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "[A][L][S][B][D][C][M]"
  },

  ["move"]= {
    switch = function()
      if bufcnt(player.toTargetDist("Assister") < 20, 60, 180) then
        return "kick"
      end
    end,
    Assister = task.staticGetBall(RECEIVE_POS2),
    Special  = task.goCmuRush(RECEIVE_POS2,player.toBallDir,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(BARYCENTER,player.toBallDir,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.stop(),
    Defender = task.stop(),
    Breaker  = task.stop(),
    Crosser  = task.stop(),    
    -- Middle   = task.multiBack(4,1),
    -- Defender = task.multiBack(4,2),
    -- Breaker  = task.multiBack(4,3),
    -- Crosser  = task.multiBack(4,4),
    match    = "[A][L][S][B][D][C][M]"
  },

  ["kick"]= {
    switch = function()
      if bufcnt(player.kickBall("Assister"), 3, 180) then
        return "receive"
      end
    end,
    Assister = task.chipPass(RECEIVE_POS2,KICK_POWER),
    Special  = task.goCmuRush(RECEIVE_POS2,player.toBallDir,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(BLOCK_POS2,player.toBallDir,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.stop(),
    Defender = task.stop(),
    Breaker  = task.stop(),
    Crosser  = task.stop(),
    -- Middle   = task.multiBack(4,1),
    -- Defender = task.multiBack(4,2),
    -- Breaker  = task.multiBack(4,3),
    -- Crosser  = task.multiBack(4,4),
    match    = "[S][L][A][B][D][C][M]"
  },

  ["receive"]= {
    switch = function()
      if bufcnt(ball.toPlayerHeadDist("Special") < 5, "fast", 180) then
        return "exit"
      end
    end,
    Assister = task.goCmuRush(RECEIVE_POS,_,_,flag.allow_dss + flag.dodge_ball),
    Special  = task.receive(ball.pos(),RECEIVE_POS2),
    Leader   = task.goCmuRush(BLOCK_POS2,_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.stop(),
    Defender = task.stop(),
    Breaker  = task.stop(),
    Crosser  = task.stop(),
    -- Middle   = task.multiBack(4,1),
    -- Defender = task.multiBack(4,2),
    -- Breaker  = task.multiBack(4,3),
    -- Crosser  = task.multiBack(4,4),
    match    = "[S][L][A][B][D][C][M]"
  },

  name = "Ref_MiddleKick_normal",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
