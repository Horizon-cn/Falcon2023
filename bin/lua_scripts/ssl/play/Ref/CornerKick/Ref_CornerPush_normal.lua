local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end

local RECEIVE_POS = CGeoPoint:new_local(100, 100)
local kickPower = 500

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") < 20 and player.toTargetDist("Special") < 20 , 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),--4
    Leader   = task.marking("First"),
    Middle   = task.marking("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "{D}{A}{B}{S}{LCM}"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 10, 3, 180) then
        return "kickBall"
      end
    end,
    Assister = task.goCmuRush(ball.pos(),_,_,flag.allow_dss),
    Leader   = task.marking("First"),
    Middle   = task.marking("Second"),
    Special  = task.goCmuRush(RECEIVE_POS,_,_,flag.allow_dss),--tiao
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match = "{D}{A}{B}{S}{LCM}"
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.passToPos(RECEIVE_POS, kickPower),
    Leader   = task.marking("First"),
    Middle   = task.marking("Second"),
    Special  = task.goCmuRush(RECEIVE_POS,_,_,flag.allow_dss),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match = "{D}{A}{B}{S}{LCM}"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(player.toBallDist("Special")<15, 3, 180) then--
        return "shootBall"
      end
    end,
    Assister = task.marking("Third"),
    Leader   = task.marking("First"),
    Middle   = task.marking("Second"),
    Special  = task.receive(ball.pos()),--position
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match = "{D}{A}{B}{S}{LCM}"
  },

["shootBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Special"), 3, 100) then--
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

  name = "Ref_CornerPush_normal",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
