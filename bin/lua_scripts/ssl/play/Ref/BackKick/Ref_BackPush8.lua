local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end
local SHOOT_POS = ball.antiYPos(CGeoPoint:new_local(0/1200*param.pitchLength,50/900*param.pitchWidth))
local kickPower = 300

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister"), 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "[A][SDBC][LM]"
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
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "[A][SDBC][LM]"
  },

  ["leaveBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister") or  player.toPointDist("Assister", ball.pos()) >50, "fast", 180) then
        return "exit"
      end
    end,
    Assister = task.chipPass(SHOOT_POS,kickPower),
    --Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "[A][SDBC][LM]"
  },

  name = "Ref_BackPush8",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
