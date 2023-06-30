local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end

--【接球点】可根据实车情况进行调整
local SHOOT_POS = ball.antiYPos(CGeoPoint:new_local(380,150))

local FRONT_POS1= ball.antiYPos(CGeoPoint:new_local(350,-150))
local FRONT_POS2= ball.antiYPos(CGeoPoint:new_local(260,0))
local FRONT_POS3= ball.antiYPos(CGeoPoint:new_local(370,210))

local TargetPos1= ball.antiYPos(CGeoPoint:new_local(410,-100))
local TargetPos2= ball.antiYPos(CGeoPoint:new_local(250,0))
local TargetPos3= ball.antiYPos(CGeoPoint:new_local(410,50))

local BlockPos=ball.antiYPos(CGeoPoint:new_local(430,-100))
--【传球力度】可根据实车情况进行调整
local kickPower = 380

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
    --match    = "[D][B][A][C][L][S][M]"
    match    = "[A][L][S][M]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 20, 20, 500) then
        return "kickBall"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS),
    Leader   = task.goCmuRush(BlockPos, _, ACC, STOP_DSS),
    Middle   = task.goCmuRush(TargetPos2,player.toPlayerHeadDir("Assister"), ACC, STOP_DSS),
    Special  = task.goCmuRush(TargetPos3,player.toPlayerHeadDir("Assister"), ACC, STOP_DSS),
    Defender = task.leftBack(),
    Breaker  = task.rightBack(),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    --match    = "[D][B][A][C][L][S][M]"
    match    = "[A][L][S][M]"
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.chipPass(SHOOT_POS, kickPower),
    Leader   = task.goCmuRush(BlockPos, _, ACC, STOP_DSS),
    Middle   = task.goCmuRush(TargetPos2,player.toBallDir("Middle"), ACC, STOP_DSS),
    Special  = task.goCmuRush(TargetPos3,player.toBallDir("Special"), ACC, STOP_DSS),
    Defender = task.leftBack(),
    Breaker  = task.rightBack(),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    --match    = "[D][B][A][C][L][S][M]"
    match    = "[A][L][S][M]"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(ball.toPlayerHeadDist("Middle") < 5, "fast", 180) then--
        return "shootBall"
      end
    end,
    Assister = task.stop(),
    Leader   = task.stop(),
    Middle   = task.protectBall(),
    Special  = task.advance(),
    Defender = task.leftBack(),
    Breaker  = task.rightBack(),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    --match    = "[D][B][A][C][L][S][M]"
    match    = "[A][L][S][M]"
  },

["shootBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Special"), 3, 1500) then--
        return "exit"
      end
    end,
    Assister = task.stop(),
    Leader   = task.stop(),
    Middle   = task.protectBall(),
    Special  = task.advance(),
    Defender = task.leftBack(),
    Breaker  = task.rightBack(),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    --match    = "[D][B][A][C][L][S][M]"
    match    = "[A][L][S][M]"
  },

  name = "Ref_IndirectCornerPush_normal_chip",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}