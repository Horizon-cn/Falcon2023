local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end

local point1=ball.antiYPos(CGeoPoint(200,130))
local point2=ball.syntYPos(CGeoPoint(190,-60))
--local point3=ball.antiYPos(CGeoPoint())
--local point4=ball.antiYPos(CGeoPoint())
--local point5=ball.antiYPos(CGeoPoint())
local FRONT_POS1 = ball.antiYPos(CGeoPoint:new_local(320, 200))
local FRONT_POS2 = ball.antiYPos(CGeoPoint:new_local(0, -200))
local FRONT_POS3 = ball.antiYPos(CGeoPoint:new_local(300, -200))
local FRONT_POS4 = ball.antiYPos(CGeoPoint:new_local(0,0))
local FRONT_POS5 = ball.antiYPos(CGeoPoint:new_local(200,-100))

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
    Middle   = task.goCmuRush(FRONT_POS5,_,_,flag.allow_dss + flag.dodge_ball),
    Special  = task.goCmuRush(FRONT_POS2,_,_,flag.allow_dss + flag.dodge_ball),
    Defender = task.goCmuRush(FRONT_POS4,_,_,flag.allow_dss + flag.dodge_ball),
    Breaker  = task.multiBack(2,1),
    Crosser  = task.multiBack(2,2),
    Goalie   = task.goalieNew(),
    match = "[A][S][D][C][B][LM]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 20, 10, 500) then
        return "kickBall"
      end
    end,
    Assister = task.staticGetBall(point1),
    Leader   = task.goCmuRush(FRONT_POS1,_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.goCmuRush(ball.pos(),player.toBallDir("Middle"),_,flag.allow_dss + flag.dodge_ball),
    Special  = task.goCmuRush(FRONT_POS2,_,_,flag.allow_dss + flag.dodge_ball),
    Defender = task.goCmuRush(FRONT_POS4,_,_,flag.allow_dss + flag.dodge_ball),
    Breaker  = task.multiBack(2,1),
    Crosser  = task.multiBack(2,2),
    Goalie   = task.goalieNew(),
    match = "[A][S][D][C][B][LM]"
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.chipPass(point1, 350),
    Leader   = task.goCmuRush(point1,player.toBallDir("Special"),_,flag.allow_dss),
    Middle   = task.goCmuRush(ball.pos(),player.toBallDir("Middle"),_,flag.allow_dss + flag.dodge_ball),
    Special  = task.goCmuRush(FRONT_POS2,_,_,flag.allow_dss + flag.dodge_ball),
    Defender = task.goCmuRush(FRONT_POS4,_,_,flag.allow_dss + flag.dodge_ball),
    Breaker  = task.multiBack(2,1),
    Crosser  = task.multiBack(2,2),
    Goalie   = task.goalieNew(),
    match = "[A][S][D][C][B][LM]"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(ball.toPlayerHeadDist("Leader") < 20, 10, 180) then--
        return "shootBall"
      end
    end,
    Assister = task.markingFront("Second"),
    Leader   = task.receivePass(ball.pos(),point1),
    --Middle   = task.goCmuRush(ball.pos(),player.toBallDir("Middle"),_,flag.allow_dss + flag.dodge_ball),
    Middle=task.stop(),
    Special  = task.goCmuRush(point2,_,_,flag.allow_dss + flag.dodge_ball),
    Defender = task.goCmuRush(FRONT_POS4,_,_,flag.allow_dss + flag.dodge_ball),
    Breaker  = task.multiBack(2,1),
    Crosser  = task.multiBack(2,2),
    Goalie   = task.goalieNew(),
    match = "[S][A][D][C][B][LM]"
  },

  ["pass"]={
    switch = function()
      if bufcnt(player.kickBall("Leader"),3,1800) then
        return "receive"
      end
    end,
    Assister = task.markingFront("Second"),
    Leader   = task.chipPass(point2,200),
    --Middle   = task.goCmuRush(ball.pos(),player.toBallDir("Middle"),_,flag.allow_dss + flag.dodge_ball),
    Middle=task.stop(),
    Special  = task.goCmuRush(point2,_,_,flag.allow_dss + flag.dodge_ball),
    Defender = task.goCmuRush(FRONT_POS4,_,_,flag.allow_dss + flag.dodge_ball),
    Breaker  = task.multiBack(2,1),
    Crosser  = task.multiBack(2,2),
    Goalie   = task.goalieNew(),
    match = "[S][A][D][C][B][LM]"
  },

  ["receive"]={
    switch=function()
      if bufcnt(ball.toPlayerHeadDist("Special") < 5,"fast",180) then
        return "shootBall"
      end
    end,
    Assister = task.markingFront("Second"),
    Leader   = task.markingFront("Third"),
    --Middle   = task.goCmuRush(ball.pos(),player.toBallDir("Middle"),_,flag.allow_dss + flag.dodge_ball),
    Middle=task.stop(),
    Special  = task.receive(ball.pos(),point2),
    Defender = task.goCmuRush(FRONT_POS4,_,_,flag.allow_dss + flag.dodge_ball),
    Breaker  = task.multiBack(2,1),
    Crosser  = task.multiBack(2,2),
    Goalie   = task.goalieNew(),
    match = "[S][A][D][C][B][LM]"
  },

  ["shootBall"]={
    switch=function()
      if(bufcnt(palyer.kickBall("Special"),3,1800)) then
        return "exit"
      end
    end,
    Assister = task.markingFront("Second"),
    Leader   = task.markingFront("Third"),
    Middle   = task.stop(),
    Special  = task.chaseNew(),
    Defender = task.stop(),
    Breaker  = task.multiBack(2,1),
    Crosser  = task.multiBack(2,2),
    Goalie   = task.goalieNew(),
    match = "[S][A][D][C][B][LM]"
  },
  name = "Ref_IndirectCornerKick",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}