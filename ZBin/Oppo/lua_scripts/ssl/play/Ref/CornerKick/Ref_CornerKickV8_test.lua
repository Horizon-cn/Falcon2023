
local chipPower = 300
local ANTI_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(150, 50))
local ANTI_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(250, 100))
local ANTI_POS_3 = ball.refAntiYPos(CGeoPoint:new_local(350, 130))


local SYNT_POS_1 = ball.refSyntYPos(CGeoPoint:new_local(250, 50))
local SYNT_POS_2 = ball.refSyntYPos(CGeoPoint:new_local(400, 60))
local SYNT_POS_3 = ball.refSyntYPos(CGeoPoint:new_local(300,180))


local SHOOT_POS = pos.passForTouch(ball.refAntiYPos(CGeoPoint:new_local(350, 130)))

local AVOID_POS = ball.refSyntYPos(CGeoPoint:new_local(400,150))

local dangerous = true


gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Defender") < 20 , 30, 180) then
        return "passBall"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS()),
    Middle   = task.goCmuRush(SYNT_POS_1),
    Defender = task.goCmuRush(ANTI_POS_1),
    Hawk     = task.goCmuRush(ANTI_POS_3),
    match    = "{A}{MDH}"
  },


  ["passBall"] = {
    switch = function ()
      if player.kickBall("Assister") or player.toBallDist("Assister") > 30 then
        print("wait")
        return "waitBall"
      else
        print("exit")
      end
    end,
    Assister = task.chipPass(SHOOT_POS(),chipPower),
    Middle   = task.goCmuRush(ANTI_POS_2),
    Defender = task.goCmuRush(SYNT_POS_2),
    Hawk     = task.goCmuRush(SYNT_POS_3),
    match    = "{ADMH}"
  },


  ["waitBall"] = {
    switch = function ()
      print("waitBall")
      if bufcnt(player.toPointDist("Middle", ANTI_POS_2) < 30, 3, 60) then
        return "shoot"
      end
    end,
    Assister = task.stop(),
    Middle   = task.goCmuRush(ANTI_POS_3),
    Defender = task.continue(),
    Hawk     = task.continue(),
    match    = "{ADMH}"
  },

  ["shoot"] = {
    switch = function ()
      print("shoot")
      if bufcnt(player.kickBall("Middle"), "fast", 180) and player.toBallDist("Assister") > 50 then
        print("exit")
        return "exit"
      end
    end,
    Assister = task.stop(),
    Middle   = task.chaseNew(),
    Defender = task.goCmuRush(AVOID_POS),
    Hawk     = task.goRightSupport(),
    match    = "{ADMH}"
  },

  name = "Ref_CornerKickV8",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
