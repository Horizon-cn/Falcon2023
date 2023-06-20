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
    Leader   = task.marking("First"),
    Middle   = task.marking("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "{A}{SDBC}{LM}"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 15, 3, 180) then
        return "leaveBall"
      end
    end,
    Assister = task.goCmuRush(ball.pos(),_,_,flag.allow_dss),
    Leader   = task.marking("First"),
    Middle   = task.marking("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "{A}{SDBC}{LM}"
  },

  ["leaveBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Middle"), "fast", 180) then
        return "exit"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.marking("First"),
    Middle   = task.marking("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "{A}{SDBC}{LM}"
  },

  name = "Ref_CornerPush8",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
