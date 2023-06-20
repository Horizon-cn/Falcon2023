local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end
<<<<<<< HEAD
local READY_POS   = ball.antiYPos(CGeoPoint:new_local(70, 150))
=======

local RECEIVE_POS = CGeoPoint:new_local(100, 100)
local kickPower = 500

>>>>>>> 3bba7c8 (“cornerpush和shootball均存在问题”)
gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") and player.toTargetDist("Middle") < 20 , 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
<<<<<<< HEAD
    Middle   = task.marking("First"),
    Leader   = task.marking("Second"),
=======
    Middle   = task.markingFront("First"),
    Leader   = task.markingFront("Second"),
>>>>>>> 3bba7c8 (“cornerpush和shootball均存在问题”)
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
<<<<<<< HEAD
    match    = "{S}{A}{D}{L}{BCM}"
=======
    match    = "{D}{A}{B}{S}{LCM}"
>>>>>>> 3bba7c8 (“cornerpush和shootball均存在问题”)
  },

  ["toBall"] = {--不拿球
    switch = function ()
<<<<<<< HEAD
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 15, 3, 180) then
=======
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 10, 3, 180) then
>>>>>>> 3bba7c8 (“cornerpush和shootball均存在问题”)
        return "kickBall"
      end
    end,
    Assister = task.goCmuRush(ball.pos(),_,_,flag.allow_dss),
    Middle   = task.marking("First"),
<<<<<<< HEAD
    Leader   = task.goCmuRush(READY_POS,_,_,flag.allow_dss),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "{S}{A}{D}{L}{BCM}"--后卫-开球-后卫-传射
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.passToPos(READY_POS,500),
    Middle   = task.marking("First"),
    Leader   = task.goCmuRush(READY_POS,_,_,flag.allow_dss),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "{S}{A}{D}{L}{BCM}"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(player.toBallDist("Leader")<15, "fast", 180) then--
        return "shootBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.marking("Second"),
    Leader   = task.receive(READY_POS),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "{S}{A}{D}{L}{BCM}"
  },

["shootBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Leader"), "fast", 180) then--
        return "exit"
      end
    end,
    Assister = task.marking("First"),
    Middle   = task.marking("Second"),
    Leader   = task.chaseNew(),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "{S}{A}{D}{L}{BCM}"
=======
    Leader   = task.marking("Second"),
    Special  = task.goCmuRush(RECEIVE_POS,_,_,flag.allow_dss),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "{D}{A}{B}{S}{LCM}"
>>>>>>> 3bba7c8 (“cornerpush和shootball均存在问题”)
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
      if bufcnt(player.kickBall("Special"), 3, 180) then--
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
<<<<<<< HEAD
    match    = "{S}{A}{D}{L}{BCM}"
=======
    match = "{D}{A}{B}{S}{LCM}"
>>>>>>> 3bba7c8 (“cornerpush和shootball均存在问题”)
  },


  name = "Ref_FrontPush_normal",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
