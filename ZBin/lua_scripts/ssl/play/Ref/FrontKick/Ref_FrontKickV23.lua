--CYM/FH 20221104


local chipPower = 250 --可用距离算
local ASIS_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(375,70))
local ASIS_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(385,110))
local ASIS_POS_3 = ball.refAntiYPos(CGeoPoint:new_local(145,-110))
local ASIS_POS_4 = ball.refAntiYPos(CGeoPoint:new_local(145,130))

local SHOOT_ASIS_POS = ball.refAntiYPos(CGeoPoint:new_local(350,-100))


local FAKE_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(270,-50))
local FAKE_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(450,210))
local FAKE_POS_11 = ball.refAntiYPos(CGeoPoint:new_local(260,-45))
local FAKE_POS_22 = ball.refAntiYPos(CGeoPoint:new_local(440,220))
--local SYNT_POS_3 = ball.refSyntYPos(CGeoPoint:new_local(300,180))


local SHOOT_POS = pos.passForTouch(ball.refAntiYPos(CGeoPoint:new_local(310,110)))
local Pre_SHOOT_POS = ball.refAntiYPos(CGeoPoint:new_local(310,110))
local dangerous = true

if ball.refPosY() > -140 and ball.refPosY() < 140 then
    chipPower=270
  else
    chipPower=350
end

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Leader") < 20 , 6, 180) then
        return "pass"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS()),
    Leader   = task.goCmuRush(Pre_SHOOT_POS),
    Special  = task.goCmuRush(FAKE_POS_2),
    Middle   = task.goCmuRush(FAKE_POS_1),
    Defender = task.leftBack(),
    Goalie   = dangerous and task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{A}{DLSMH}{E}"
  },

 -- ["change"] = {
 --    switch = function ()
 --      if bufcnt(player.toTargetDist("Leader") < 20 , 30, 180) then
 --        return "pass"
 --      end
 --    end,
 --    Assister = task.staticGetBall(SHOOT_POS()),
 --    -- Leader   = task.goCmuRush(ASIS_POS_3),
 --    -- Special  = task.goCmuRush(ASIS_POS_2),
 --    -- Middle   = task.goCmuRush(ASIS_POS_1),
 --    Leader   = task.goCmuRush(SHOOT_POS),
 --    Special  = task.goCmuRush(FAKE_POS_2),
 --    Middle   = task.goCmuRush(FAKE_POS_1),
 --    Defender = task.leftBack(),
 --    Goalie   = task.goalie(),
 --    Engine   = task.singleBack(),
 --    Hawk     = task.rightBack(),
 --    match    = "{A}{DLSMH}{E}"
 --  }, 

  

  ["pass"] = {
    switch = function ()
      if player.kickBall("Assister") or player.toBallDist("Assister") > 30 then
        print("wait")
        return "waitBall"
      else
        print("exit")
      end
    end,
    Assister = task.chipPass(SHOOT_POS(),chipPower),
    Leader   = task.goCmuRush(Pre_SHOOT_POS,player.toPlayerDir("Assister")),
    Special  = task.goCmuRush(FAKE_POS_22),
    Middle   = task.goCmuRush(FAKE_POS_11),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{ADLSMEH}"
  },


  ["waitBall"] = {
    switch = function ()
      print("waitBall")
      if bufcnt(player.toPointDist("Leader", SHOOT_POS) < 10, 3, 60) then
        return "shoot"
      end
    end,
    Assister = task.goCmuRush(SHOOT_ASIS_POS),
    Leader   = task.goCmuRush(Pre_SHOOT_POS,player.toPlayerDir("Assister")),
    Special  = task.continue(),
    Middle   = task.continue(),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{ADL}{EH}{SM}"
  },

  ["shoot"] = {
    switch = function ()
      print("shoot")
      if bufcnt(player.kickBall("Leader"), "fast", 120) then
        print("exit")
        return "exit"
      end
    end,
    Assister = task.goCmuRush(ASIS_POS_4),
    Leader   = task.shootV2(),
    Special  = task.continue(),
    Middle   = task.continue(),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{ADL}{EH}{SM}"
  },

  name = "Ref_FrontKickV23",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
