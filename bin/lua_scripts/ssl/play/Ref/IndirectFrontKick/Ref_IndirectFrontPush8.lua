local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end
local SHOOT_POS = ball.syntYPos(CGeoPoint:new_local(500/1200*param.pitchLength,-80/900*param.pitchWidth))
local function def_chipPower()
  if math.abs(ball.posX()) < 100 then
    if math.abs(ball.posY()) > 300 then 
      return 1000
    elseif math.abs(ball.posY())> 285 then
      return 1000
    elseif math.abs(ball.posY()) > 200 then 
      return 800
    else
      return 600
    end
  elseif math.abs(ball.posX()) < 200 then
    if math.abs(ball.posY()) > 300 then 
      return 600
    elseif math.abs(ball.posY())> 285 then
      return 500
    elseif math.abs(ball.posY()) > 270 then 
      return 450
    elseif math.abs(ball.posY()) > 200 then 
      return 300
    else
      return 50
    end
  else
    if math.abs(ball.posY()) > 300 then 
      return 450
    elseif math.abs(ball.posY())> 285 then
      return 370
    elseif math.abs(ball.posY()) > 270 then 
      return 330
    elseif math.abs(ball.posY()) > 200 then 
      return 250
    else
      return 10
    end
  end
end

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") < 20 , 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.markingFront("Third"),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[A][DBC][LSM]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 5, 3, 180) then
        return "leaveBall"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.markingFront("Third"),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[A][DBC][LSM]"
  },

  ["leaveBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) > 50, "fast", 180) then
        return "exit"
      end
    end,
    Assister = task.chipPass(SHOOT_POS,def_chipPower()),
    --Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.markingFront("Third"),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[A][DBC][LSM]"
  },

  name = "Ref_IndirectFrontPush8",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
