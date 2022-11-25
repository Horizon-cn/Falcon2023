--CYM/FH 20221104

local k = 0.025
local ASIS_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(260,110))
local ASIS_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(408,77))
local ASIS_POS_3 = ball.refAntiYPos(CGeoPoint:new_local(413,34))
local ASIS_POS_4 = ball.refAntiYPos(CGeoPoint:new_local(145,130))

local SHOOT_ASIS_POS = ball.refAntiYPos(CGeoPoint:new_local(340,-90))


local FAKE_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(270,-50))
local FAKE_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(450,210))
local FAKE_POS_11 = ball.refAntiYPos(CGeoPoint:new_local(260,-45))
local FAKE_POS_22 = ball.refAntiYPos(CGeoPoint:new_local(440,220))
--local SYNT_POS_3 = ball.refSyntYPos(CGeoPoint:new_local(300,180))


local SHOOT_POS = pos.passForTouch(ball.refAntiYPos(CGeoPoint:new_local(310,100)))
local Pre_SHOOT_POS = ball.refAntiYPos(CGeoPoint:new_local(350,120))
local dangerous = true

--[[local chipPower = function()
  local yy = 0
  if ball.refPosY() >= 0 then
    yy = ball.refPosY()+110
  else
    yy = 110-ball.refPosY()
  end

  local xx = 0
  if ball.posX() >= 310 then
    xx = ball.posX()-310
  else
    xx = 310-ball.posX()
  end

  local k = 0.025
  local len = xx+yy
  return k*len
end--]]


local chipPower = function(p)
  local pos
  local k = 0.025
  if type(p) == "function" then
    pos = p()
  else
    pos = p
  end
  return k*ball.toPointDist(pos)
end


gPlayTable.CreatePlay{

  firstState = "start",

--[[  ["start"] = {
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
  },--]]

 ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Leader") < 20 , 30, 180) then
        return "pass"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS()),
    -- Leader   = task.goCmuRush(ASIS_POS_3),
    -- Special  = task.goCmuRush(ASIS_POS_2),
    -- Middle   = task.goCmuRush(ASIS_POS_1),
    Leader   = task.goCmuRush(ASIS_POS_1),
    Special  = task.goCmuRush(ASIS_POS_2),
    Middle   = task.goCmuRush(ASIS_POS_3),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{A}{DLSMH}{E}"
  }, 

  

  ["pass"] = {
    switch = function ()
      if player.kickBall("Assister") or player.toBallDist("Assister") > 30 then
        print("wait")
        print("chipPower",chipPower(SHOOT_POS()))
        return "shoot"
      else
        print("exit")
      end
      
    end,
    
    Assister = task.chipPass(SHOOT_POS()),
    Leader   = task.goCmuRush(Pre_SHOOT_POS),
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
      if bufcnt(player.toPointDist("Special",FAKE_POS_22) < 30, 3, 60) then
        return "shoot"
      end
    end,
    Assister = task.goCmuRush(SHOOT_ASIS_POS),
    Leader   = task.continue(),
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