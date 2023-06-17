local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end

gPlayTable.CreatePlay{

  firstState = "init",

  ["init"] = {
    switch = function ()
      if false then
        return "exit"
      end
    end,
    Assister = task.defendKick(),
    Middle   = task.markingFront("First"),
    Leader   = task.rightBack(),
    Special  = task.leftBack(),
    Defender = task.sideBack(),
    Goalie   = task.goalieNew(),
    match    = "{LS}{A}{M}{D}"
  },

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") and player.toTargetDist("Middle") < 20 , 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.goCmuRush(WAIT_BALL_POS(0),_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.rightBack(),
    Special  = task.leftBack(),
    Defender = task.sideBack(),
    Goalie   = task.goalieNew(),
    match    = "{LS}{A}{M}{D}"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 15, 3, 180) then
        return "leaveBall"
      end
    end,
    Assister = task.goCmuRush(ball.pos(),_,_,flag.allow_dss),
    Middle   = task.goCmuRush(WAIT_BALL_POS(0),_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.rightBack(),
    Special  = task.leftBack(),
    Defender = task.sideBack(),
    Goalie   = task.goalieNew(),
    match    = "{LS}{A}{M}{D}"
  },

  ["leaveBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Middle"), "fast", 180) then
        return "exit"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.rightBack(),
    Special  = task.leftBack(),
    Middle   = task.advance(),
    Defender = task.sideBack(),
    Goalie   = task.goalieNew(),
    match    = "{LS}{A}{M}{D}"
  },

  name = "Ref_CornerPush8",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
