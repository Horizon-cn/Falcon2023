
local chipPower = 250
local ANTI_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(150, 50))
local ANTI_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(300, 100))
local ANTI_POS_3 = ball.refAntiYPos(CGeoPoint:new_local(450, 130))


local SYNT_POS_1 = ball.refSyntYPos(CGeoPoint:new_local(200, 50))
local SYNT_POS_2 = ball.refSyntYPos(CGeoPoint:new_local(400, 60))
local SYNT_POS_3 = ball.refSyntYPos(CGeoPoint:new_local(300,180))


local SHOOT_POS = pos.passForTouch(ball.refAntiYPos(CGeoPoint:new_local(400, 130)))

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
    Leader   = task.rightBack(),
    Special  = task.leftBack(),
    Middle   = task.goCmuRush(SYNT_POS_1),
    Defender = task.goCmuRush(ANTI_POS_1),
    Goalie   = dangerous and task.goalieNew(),
    Engine   = task.goLWPassPos("Assister"),
    Hawk     = task.goCmuRush(ANTI_POS_3),
    match    = "{A}{LS}{M}{DEH}"
  },


  ["passBall"] = {
    switch = function ()
      --chip_power_func()
      if player.kickBall("Assister") or player.toBallDist("Assister") > 30 then
        return "waitBall"
      end
    end,
    Assister = task.chipPass(SHOOT_POS(),chipPower),
    Leader   = task.rightBack(),
    Special  = task.leftBack(),
    Middle   = task.goCmuRush(ANTI_POS_2),
    Defender = task.goCmuRush(SYNT_POS_2),
    Goalie   = task.goalieNew(),
    Engine   = task.goLWPassPos("Assister"),
    Hawk     = task.goCmuRush(SYNT_POS_3),
    match    = "{A}{LS}{M}{DEH}"
  },


  ["waitBall"] = {
    switch = function ()
      print("waitBall")
      if bufcnt(player.toPointDist("Defender", SYNT_POS_2) < 30, 3, 60) then
        return "shoot"
      end
    end,
    Assister = task.stop(),
    Leader   = task.rightBack(),
    Special  = task.leftBack(),
    Middle   = task.goCmuRush(ANTI_POS_3),
    Defender = task.continue(),
    Goalie   = task.goalieNew(),
    Engine   = task.goLWPassPos("Assister"),
    Hawk     = task.continue(),
    match    = "{A}{LS}{M}{DEH}"
  },

  ["shoot"] = {
    switch = function ()
      print("shoot")
      if bufcnt(player.kickBall("Defender"), "fast", 180) then
        print("exit")
        return "exit"
      end
    end,
    Assister = task.stop(),
    Leader   = task.rightBack(),
    Special  = task.leftBack(),
    Middle   = task.shootV2(),
    Defender = task.goLeftSupport(),
    Goalie   = task.goalieNew(),
    Engine   = task.goLWPassPos("Assister"),
    Hawk     = task.goRightSupport(),
    match    = "{A}{LS}{M}{DEH}"
  },

  name = "Ref_CornerKickV8",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
