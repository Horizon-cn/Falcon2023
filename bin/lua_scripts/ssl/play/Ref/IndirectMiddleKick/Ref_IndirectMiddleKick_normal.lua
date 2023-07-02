local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end

local RECEIVE_POS = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local(550, 120))()
  else
    return ball.syntYPos(CGeoPoint:new_local(560, 0))()
  end
end
local BLOCK_POS = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local(ball.posX(),350))()
  else
    return ball.syntYPos(CGeoPoint:new_local(ball.posX(),200))()
  end
end
local BARYCENTER = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local((550+ball.posX())/2,235))()
  else
    return ball.syntYPos(CGeoPoint:new_local((560+ball.posX())/2,250))() 
  end
end
local BLOCK_POS2 = function()
  return ball.syntYPos(CGeoPoint:new_local(430, 0))()
end
local RECEIVE_POS2 = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local(250, 60))()
  else
    return ball.syntYPos(CGeoPoint:new_local(170, 80))()
  end
end
local SHOOT_POS = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local(510, 70))()
  else
    return ball.syntYPos(CGeoPoint:new_local(490, 80))()
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
    Special  = task.goCmuRush(BLOCK_POS,_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(BARYCENTER,_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "[A][B][C][S][D][L][M]"
  },

  ["move"]= {
    switch = function()
      if bufcnt(player.toTargetDist("Assister") < 20, 60, 180) then
        return "kick"
      end
    end,
    Assister = task.staticGetBall(RECEIVE_POS2),
    Special  = task.goCmuRush(RECEIVE_POS2,_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(BARYCENTER,_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    match    = "[A][B][C][S][D][L][M]"
  },

  ["kick"]= {
    switch = function()
      if bufcnt(player.kickBall("Assister"), 3, 180) then
        return "receive"
      end
    end,
    Assister = task.chipPass(RECEIVE_POS2,KICK_POWER),
    Special  = task.goCmuRush(RECEIVE_POS2,_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(BLOCK_POS2,_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    match    = "[A][B][C][S][D][L][M]"
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
    Middle   = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    match    = "[S][B][C][A][D][L][M]"
  },

  name = "Ref_IndirectMiddleKick_normal",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
