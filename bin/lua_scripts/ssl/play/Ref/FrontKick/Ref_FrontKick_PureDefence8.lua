local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end
local SHOOT_POS = ball.syntYPos(CGeoPoint:new_local(500/1200*param.pitchLength,0/900*param.pitchWidth))
local KICK_POWER=function()
  return 13.6*math.sqrt(ball.toPointDist(SHOOT_POS()))
end

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") < 20 , 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),player.toPointDir(SHOOT_POS),_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][A][BC][S][LM]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 20, 100, 500) then
        return "leaveBall"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][A][BC][S][LM]"
  },

  ["leaveBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) > 50, "fast", 180) then
        return "exit"
      end
    end,
    Assister = task.chipPass(SHOOT_POS,KICK_POWER),
    --Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.sideBack(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[D][A][BC][S][LM]"
  },

  name = "Ref_FrontKick_PureDefence8",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
