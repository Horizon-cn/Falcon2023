local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end

local FRONT_POS1=ball.antiYPos(CGeoPoint(200,180))
local FRONT_POS2=ball.antiYPos(CGeoPoint(160,-60))
local FRONT_POS3=ball.antiYPos(CGeoPoint(160,60))
local passPos=ball.antiYPos(CGeoPoint(270,70))
local blockPos1=CGeoPoint(340,-50)
local blockPos2=CGeoPoint(340,0)

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Assister") < 20, 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS,_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(FRONT_POS1,_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.goCmuRush(ball.pos(),_,_,flag.allow_dss + flag.dodge_ball),
    Special  = task.protectBall(),
    Defender = task.multiBack(2,1),
    Breaker  = task.multiBack(2,2),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][S][M]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 20, 10, 500) then
        return "kickBall"
      end
    end,
    Assister = task.staticGetBall(passPos),
    Leader   = task.goCmuRush(passPos,_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.markingFront("Second"),
    Special  = task.protectBall(),
    Defender = task.multiBack(2,1),
    Breaker  = task.multiBack(2,2),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][S][M]"
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.chipPass(passPos, 250),
    Leader   = task.goCmuRush(passPos,player.toPlayerDir("Assister"),_,flag.allow_dss),
    Middle   = task.markingFront("second"),
    Special  = task.protectBall(),
    Defender = task.multiBack(2,1),
    Breaker  = task.multiBack(2,2),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][S][M]"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(ball.toPlayerHeadDist("Leader") < 20, 10, 180) then--
        return "shootBall"
      end
    end,
    Assister = task.markingFront("Second"),
    Leader   = task.receivePass(ball.pos(),passPos),
    Middle   = task.markingFront("Third"),
    Special  = task.protectBall(),
    Defender = task.multiBack(2,1),
    Breaker  = task.multiBack(2,2),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][S][M]"
  },

  ["shootBall"]={
    switch=function()
      if(bufcnt(player.kickBall("Leader"),3,1800)) then
        return "exit"
      end
    end,
    Assister = task.markingFront("Second"),
    Leader   = task.advance(),
    Middle   = task.markingFront("Third"),
    Special  = task.protectBall(),
    Defender = task.multiBack(2,1),
    Breaker  = task.multiBack(2,2),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match    = "[D][B][A][C][L][S][M]"
  },
  name = "Ref_IndirectCornerKick",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}