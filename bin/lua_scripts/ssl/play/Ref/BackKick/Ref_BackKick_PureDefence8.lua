local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end
local SHOOT_POS = ball.antiYPos(CGeoPoint:new_local(0/1200*param.pitchLength,0/900*param.pitchWidth))
local KICK_POWER=function()
  return 13.6*math.sqrt(ball.toPointDist(SHOOT_POS()))
end

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister"), 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),player.toPointDir(SHOOT_POS),_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.multiBack(3,1),
    Defender = task.multiBack(3,2),
    Breaker  = task.multiBack(3,3),
    Crosser  = task.sideBack(),
    Goalie   = task.goalieNew(),
    match    = "[D][A][SB][C][LM]"
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
    Special  = task.multiBack(3,1),
    Defender = task.multiBack(3,2),
    Breaker  = task.multiBack(3,3),
    Crosser  = task.sideBack(),
    Goalie   = task.goalieNew(),
    match    = "[D][A][SB][C][LM]"
  },

  ["leaveBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister") or  player.toPointDist("Assister", ball.pos()) >50, "fast", 180) then
        return "exit"
      end
    end,
    Assister = task.chipPass(SHOOT_POS,KICK_POWER),
    --Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.multiBack(3,1),
    Defender = task.multiBack(3,2),
    Breaker  = task.multiBack(3,3),
    Crosser  = task.sideBack(),
    Goalie   = task.goalieNew(),
    match    = "[D][A][SB][C][LM]"
  },

  name = "Ref_BackKick_PureDefence8",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
