local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end

--【接球点】可根据实车情况进行调整
local RECEIVE_POS = ball.syntYPos(CGeoPoint:new_local(170, 150))
--【传球力度】可根据实车情况进行调整
local kickPower = 300

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") < 20, 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS,_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.markingFront("First"),
    Middle   = task.markingFront("Second"),
    Special  = task.goCmuRush(RECEIVE_POS,player.toBallDir("Special"),_,flag.allow_dss),
    Defender = task.multiBack(2,1),
    Breaker  = task.multiBack(2,2),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "[A][S][D][C][B][LM]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 20, 10, 500) then
        return "kickBall"
      end
    end,
    Assister = task.staticGetBall(RECEIVE_POS),
    Leader   = task.markingFront("First"),
    Middle   = task.markingFront("Second"),
    Special  = task.goCmuRush(RECEIVE_POS,player.toBallDir("Special"),_,flag.allow_dss),
    Defender = task.multiBack(2,1),
    Breaker  = task.multiBack(2,2),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "[A][S][D][C][B][LM]"
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.chipPass(RECEIVE_POS, kickPower),
    Leader   = task.markingFront("First"),
    Middle   = task.markingFront("Second"),
    Special  = task.goCmuRush(RECEIVE_POS,player.toBallDir("Special"),_,flag.allow_dss),
    Defender = task.multiBack(2,1),
    Breaker  = task.multiBack(2,2),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "[A][S][D][C][B][LM]"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(ball.toPlayerHeadDist("Special") < 5, "fast", 180) then--
        return "shootBall"
      end
    end,
    Assister = task.stop(),
    Leader   = task.markingFront("Second"),
    Middle   = task.markingFront("Third"),
    Special  = task.receive(ball.pos(),RECEIVE_POS),
    Defender = task.multiBack(2,1),
    Breaker  = task.multiBack(2,2),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "[S][A][D][C][B][LM]"
  },

["shootBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Special"), 3, 1800) then--
        return "exit"
      end
    end,
    Assister = task.stop(),
    Leader   = task.markingFront("Second"),
    Middle   = task.markingFront("Third"),
    Special  = task.advance(),
    Defender = task.multiBack(2,1),
    Breaker  = task.multiBack(2,2),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "[S][A][D][C][B][LM]"
  },

  name = "Ref_IndirectCornerPush_normal_chip",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}