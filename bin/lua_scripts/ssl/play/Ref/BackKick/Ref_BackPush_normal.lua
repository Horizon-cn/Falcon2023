local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") and player.toTargetDist("Middle") < 20 , 10, 180) then
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
    match    = "{D}{A}{B}{S}{LCM}"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 15, 3, 180) then
        return "kickBall"
      end
    end,
    Assister = task.goCmuRush(ball.pos(),_,_,flag.allow_dss),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.goCmuRush(READY_POS,_,_,flag.allow_dss),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "{D}{A}{B}{S}{LCM}"
  },

["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.passToPos(READY_POS,500),
    Leader   = task.marking("First"),
    Middle   = task.marking("Second"),
    Special  = task.goCmuRush(READY_POS,_,_,flag.allow_dss),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match = "{D}{A}{B}{S}{LCM}"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(player.toBallDist("Special")<15, "fast", 180) then--
        return "shootBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.marking("First"),
    Middle   = task.marking("Second"),
    Special  = task.receive(READY_POS),--position
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match = "{D}{A}{B}{S}{LCM}"
  },

["shootBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Special"), "fast", 180) then--
        return "exit"
      end
    end,
    Assister = task.marking("Third"),
    Leader   = task.marking("First"),
    Middle   = task.marking("Second"),
    Special  = task.chaseNew(),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match = "{D}{A}{B}{S}{LCM}"
  },

  ["leaveBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Middle"), "fast", 180) then
        return "exit"
      end
    end,
    Assister = task.chaseNew(),
    --Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "{D}{A}{B}{S}{LCM}"
  },

  name = "Ref_BackPush_normal",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
