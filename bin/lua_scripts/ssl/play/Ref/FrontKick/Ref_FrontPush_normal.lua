local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end
local READY_POS   = ball.antiYPos(CGeoPoint:new_local(70, 150))
gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") and player.toTargetDist("Middle") < 20 , 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.marking("First"),
    Leader   = task.marking("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "{S}{A}{D}{L}{BCM}"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 15, 3, 180) then
        return "kickBall"
      end
    end,
    Assister = task.goCmuRush(ball.pos(),_,_,flag.allow_dss),
    Middle   = task.marking("First"),
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
  },

  ["leaveBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Middle"), "fast", 180) then
        return "exit"
      end
    end,
    Assister = task.chaseNew(),
    --Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.marking("First"),
    Leader   = task.marking("Second"),
    Special  = task.marking("Third"),
    Defender = task.multiBack(3,1),
    Breaker  = task.multiBack(3,2),
    Crosser  = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "{S}{A}{D}{L}{BCM}"
  },

  name = "Ref_FrontPush_normal",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
