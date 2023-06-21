local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end

local RECEIVE_POS = CGeoPoint:new_local(100, 100)
local kickPower = 500

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
    Middle   = task.marking("First"),
    Leader   = task.marking("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "{D}{A}{B}{S}{LCM}"
    match    = "{D}{A}{B}{L}{SCM}"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 15, 3, 180) then
        return "kickBall"
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 10, 3, 180) then
        return "kickBall"
      end
    end,
    Assister = task.goCmuRush(ball.pos(),_,_,flag.allow_dss),
    Middle   = task.marking("First"),
    Leader   = task.goCmuRush(RECEIVE_POS,_,_,flag.allow_dss),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "{D}{A}{B}{L}{SCM}"
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.passToPos(RECEIVE_POS, kickPower),
    Middle   = task.marking("First"),
    Leader   = task.goCmuRush(RECEIVE_POS,_,_,flag.allow_dss),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "{D}{A}{B}{L}{SCM}"
  },

["receiveBall"] = {
    switch = function ()
      if bufcnt(player.toBallDist("Leader")<15, 3, 180) then--
        return "shootBall"
      end
    end,
    Assister = task.marking("First"),
    Middle   = task.marking("Second"),
    Leader   = task.receive(ball.pos()),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "{D}{A}{B}{S}{LCM}"
    match = "{D}{A}{B}{L}{SCM}"
  },

  ["shootBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Leader"), 3, 180) then--
        return "exit"
      end
    end,
    Assister = task.marking("First"),
    Middle   = task.marking("Second"),
    Leader   = task.chaseNew(),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "{D}{A}{B}{S}{LCM}"
    match = "{D}{A}{B}{L}{SCM}"
  },

  name = "Ref_BackPush_normal",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
