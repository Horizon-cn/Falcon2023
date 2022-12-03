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


local chipPower = function(p)
  local pos
  local k = 0.02
  if type(p) == "function" then
    pos = p()
  else
    pos = p
  end
  if math.abs(pos:y()) < 200 then
    return 210 
  end
  return k*ball.toPointDist(pos)
end


gPlayTable.CreatePlay{

  firstState = "start",

 ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Leader") < 20 , 30, 180) then
        return "pass"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS()),
    Leader   = task.goCmuRush(ASIS_POS_1,_,_,flag.allow_dss),
    Special  = task.goMWPassPos("Assister"),
    Middle   = task.marking("First"),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{A}{DH}{LSM}{E}"
  }, 

  

  ["pass"] = {
    switch = function ()
      if player.kickBall("Assister") or player.toBallDist("Assister") > 30 then
        return "shoot"
      else
        print("exit")
      end
      
    end,
    
    Assister = task.chipPass(SHOOT_POS(),chipPower(SHOOT_POS())),
    Leader   = task.goCmuRush(Pre_SHOOT_POS,_,_,flag.allow_dss),
    Special  = task.goMWPassPos("Assister"),
    Middle   = task.marking("First"),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{A}{DH}{LSM}{E}"
  },

        
  ["waitBall"] = {
    switch = function ()
      print("waitBall")
      if bufcnt(player.toPointDist("Special",FAKE_POS_22) < 30, 3, 60) then
        return "shoot"
      end
    end,
    Assister = task.goCmuRush(SHOOT_ASIS_POS,_,_,flag.allow_dss),
    Leader   = task.continue(),
    Special  = task.goMWPassPos("Assister"),
    Middle   = task.marking("First"),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{A}{DEH}{LSM}"
  },

  ["shoot"] = {
    switch = function ()
      print("shoot")
      if bufcnt(player.kickBall("Leader"), "fast", 120) then
        print("exit")
        return "exit"
      end
    end,
    Assister = task.goCmuRush(ASIS_POS_4,_,_,flag.allow_dss),
    Leader   = task.shootV2(),
    Special  = task.goMWPassPos("Assister"),
    Middle   = task.marking("First"),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{L}{DH}{AE}{SM}"
  },

  name = "Ref_FrontKickV23",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
