local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end

--【接球点】可根据实车情况进行调整
local SHOOT_POS = ball.antiYPos(CGeoPoint:new_local(400, 200))
local FRONT_POS1= ball.antiYPos(CGeoPoint:new_local(400,-140))
local FRONT_POS2= ball.antiYPos(CGeoPoint:new_local(180,150))
local FRONT_POS3= ball.antiYPos(CGeoPoint:new_local(500,260))
local TargetPos1= ball.syntYPos(CGeoPoint:new_local(430,-100))
local TargetPos2= ball.syntYPos(CGeoPoint:new_local(250,0))
local TargetPos3= ball.syntYPos(CGeoPoint:new_local(170,400))
--【传球力度】可根据实车情况进行调整
local kickPower = 400

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") < 20, 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS,_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(FRONT_POS1, _, ACC, STOP_DSS),
    Middle   = task.goCmuRush(FRONT_POS2, _, ACC, STOP_DSS),
    Special  = task.goCmuRush(FRONT_POS3, _, ACC, STOP_DSS),
    Defender = task.leftBack(),
    Breaker  = task.rightBack(),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "[D][B][A][C][M][L][S]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 20, 10, 500) then
        return "kickBall"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS),
    Leader   = task.goCmuRush(FRONT_POS1, _, ACC, STOP_DSS),
    Middle   = task.goCmuRush(FRONT_POS2, _, ACC, STOP_DSS),
    Special  = task.goCmuRush(FRONT_POS3, _, ACC, STOP_DSS),
    Defender = task.leftBack(),
    Breaker  = task.rightBack(),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "[D][B][A][C][M][L][S]"
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.chipPass(SHOOT_POS, kickPower),
    Leader   = task.goCmuRush(TargetPos1, _, ACC, STOP_DSS),
    Middle   = task.goCmuRush(TargetPos2, _, ACC, STOP_DSS),
    Special  = task.goCmuRush(TargetPos3, _, ACC, STOP_DSS),
    Defender = task.leftBack(),
    Breaker  = task.rightBack(),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "[D][B][A][C][M][L][S]"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(ball.toPlayerHeadDist("Middle") < 5, "fast", 180) then--
        return "shootBall"
      end
    end,
    Assister = task.markingFront("Third"),
    Leader   = task.protectBall(),
    Middle   = task.advance(),
    Special  = task.chaseNew(),
    Defender = task.leftBack(),
    Breaker  = task.rightBack(),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "[D][B][A][C][M][L][S]"
  },

["shootBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Middle"), 3, 180) then--
        return "exit"
      end
    end,
    Assister = task.markingFront("Third"),
    Leader   = task.protectBall(),
    Middle   = task.advance(),
    Special  = task.chaseNew(),
    Defender = task.leftBack(),
    Breaker  = task.rightBack(),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "[D][B][A][C][M][L][S]"
  },

  name = "Ref_IndirectMiddlePush_normal_chip",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}