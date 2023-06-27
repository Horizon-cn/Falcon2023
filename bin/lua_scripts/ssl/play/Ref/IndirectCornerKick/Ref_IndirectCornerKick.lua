local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end

local FRONT_POS1=CGeoPoint(200,180)
local FRONT_POS2=CGeoPoint(160,-60)
local FRONT_POS3=CGeoPoint(160,60)
local passPos=CGeoPoint(270,70)
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
    Middle   = task.goCmuRush(blockPos1,_,_,flag.allow_dss + flag.dodge_ball),
    Special  = task.goCmuRush(blockPos2,_,_,flag.allow_dss + flag.dodge_ball),
    match = "[A][L][M][S]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 20, 10, 500) then
        return "kickBall"
      end
    end,
    Assister = task.staticGetBall(passPos),
    Leader   = task.goCmuRush(FRONT_POS1,_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.goCmuRush(blockPos1,_,_,flag.allow_dss + flag.dodge_ball),
    Special  = task.goCmuRush(blockPos2,_,_,flag.allow_dss + flag.dodge_ball),
    match = "[A][L][M][S]"
  },

  ["kickBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), "fast", 180) then
        return "receiveBall"
      end
    end,
    Assister = task.chipPass(passPos, 250),
    Leader   = task.goCmuRush(passPos,player.toPlayerDir("Assister"),_,flag.allow_dss),
    Middle   = task.goCmuRush(blockPos1,_,_,flag.allow_dss + flag.dodge_ball),
    Special  = task.goCmuRush(blockPos2,_,_,flag.allow_dss + flag.dodge_ball),
    match = "[A][L][M][S]"
  },

  ["receiveBall"] = {
    switch = function ()
      if bufcnt(ball.toPlayerHeadDist("Leader") < 20, 10, 180) then--
        return "shootBall"
      end
    end,
    Assister = task.markingFront("Second"),
    Leader   = task.receivePass(ball.pos(),passPos),
    Middle   = task.goCmuRush(blockPos1,_,_,flag.allow_dss + flag.dodge_ball),
    Special  = task.goCmuRush(blockPos2,_,_,flag.allow_dss + flag.dodge_ball),
    match = "[A][L][M][S]"
  },

  ["shootBall"]={
    switch=function()
      if(bufcnt(player.kickBall("Leader"),3,1800)) then
        return "exit"
      end
    end,
    Assister = task.markingFront("Second"),
    Leader   = task.advance(),
    Middle   = task.protectBall(),
    Special  = task.goCmuRush(blockPos1,_,_,flag.allow_dss + flag.dodge_ball),
    match = "[A][L][M][S]"
  },
  name = "Ref_IndirectCornerKick",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}