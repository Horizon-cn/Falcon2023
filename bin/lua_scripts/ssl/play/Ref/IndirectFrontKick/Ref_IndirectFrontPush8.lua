local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end
local SHOOT_POS = ball.antiYPos(CGeoPoint:new_local(300, 50))

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") < 20 , 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.marking("First"),
    Leader   = task.marking("Second"),
    Special  = task.marking("Third"),
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
    Middle   = task.marking("First"),
    Leader   = task.marking("Second"),
    Special  = task.marking("Third"),
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
    Assister = task.justKick(),
    --Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.marking("First"),
    Leader   = task.marking("Second"),
    Special  = task.marking("Third"),
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
