----------------------------------------------------------
-----             SRC lua             ------
-----   中场任意球，使用范围中线0~125   ------
-----          SCJ 2020/11/10 改      ------
-- 用在中场靠中间位置的定位球，主要要考虑到球的y值会在正负之前跳动
---11/13改 平传 receiveShoot 
local halfPitchX = param.pitchLength/2    -- 半场长度
local halfPitchY = param.pitchWidth/2   -- 半场宽度
local halfGoalW = param.goalWidth/2

local MAKE_POS_ORG    = CGeoPoint:new_local(100, -250)
local RIGHT_POS   = ball.refSyntYPos(CGeoPoint:new_local(280, 220))
local INNER_POS   = ball.refSyntYPos(CGeoPoint:new_local(350, 220))
local RIGHT_POS2  = ball.refSyntYPos(CGeoPoint:new_local(250, 250))
local MAKE_POS    = ball.refAntiYPos(MAKE_POS_ORG)
local READY_POS   = ball.refSyntYPos(CGeoPoint:new_local(80, -150))
local SHOOT_POS   = ball.refSyntYPos(CGeoPoint:new_local(70, -150))
local MASK_POS    = ball.refSyntYPos(CGeoPoint:new_local(320, 100))
local SHOOT_POS2  = ball.refSyntYPos(CGeoPoint:new_local(280, -130))
local SHOOT_POS3  = ball.refSyntYPos(CGeoPoint:new_local(50, 100))
local GOALIE_POS = {
  ball.refSyntYPos(CGeoPoint:new_local(-0.5*halfPitchX,0.3*halfPitchY)),
  ball.refSyntYPos(CGeoPoint:new_local(-0.3*halfPitchX,0.3*halfPitchY)),
  ball.refSyntYPos(CGeoPoint:new_local(0.1*halfPitchX,0.3*halfPitchY)),
  FINAL_SHOOT_POS,
}

gPlayTable.CreatePlay{

firstState = "getready",

["getready"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Special")<30 or
      player.toTargetDist("Leader")<30, "normal") then
      return "startball"
    end
  end,
  --Assister = task.goCmuRush(ball.pos())
  Assister = task.getBall(MAKE_POS_ORG),
  Leader   = task.goCmuRush(CGeoPoint:new_local(0,120)),
  Special  = task.goCmuRush(CGeoPoint:new_local(0,-120)),
 Defender = task.goCmuRush(READY_POS),
  Middle   = task.goCmuRush(RIGHT_POS2),
  Goalie   = task.runMultiPos(GOALIE_POS, false, 30, _, 600),
  match    = "{A}[LDSM]"
},

["startball"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Special")<30 and
      player.toTargetDist("Leader")<30, 1, 180) then
      return "getball"
    end
  end,
  Assister = task.getBall(MAKE_POS_ORG),
  Middle   = task.goCmuRush(RIGHT_POS2),
  Special  = task.goCmuRush(RIGHT_POS),
  Leader   = task.goCmuRush(MAKE_POS, player.toBallDir("Leader")),
  Defender = task.goCmuRush(READY_POS),
  Goalie   = task.runMultiPos(GOALIE_POS, false, 30, _, 600),
  match    = "{A}[DLSM]"
},

["getball"] = {
  switch = function ()
    if bufcnt(true, 20) then
      return "chippass"
    end
  end,
  Assister = task.getBall(MAKE_POS_ORG),
  Middle   = task.goCmuRush(RIGHT_POS2),
  Special  = task.goCmuRush(RIGHT_POS),
  Leader   = task.goCmuRush(MAKE_POS, player.toBallDir("Leader")),
  Defender = task.goCmuRush(READY_POS, player.toBallDir("Defender")),
  Goalie   = task.goalie(),
  match    = "{ADLSM}"
},

["chippass"] = {
  switch = function ()
    if  player.kickBall("Assister") or
      player.toBallDist("Assister") > 20 then
      return "fixgoto"
    end
  end,
  Assister = task.chipPass("Defender",200),
  Middle   = task.goCmuRush(RIGHT_POS2),
  Special  = task.goCmuRush(RIGHT_POS),
  Leader   = task.goCmuRush(MAKE_POS, player.toBallDir("Leader")),
  Defender = task.goCmuRush(READY_POS,player.toBallDir("Defender")),
  Goalie   = task.goalie(),
  match    = "{ADLSM}"
},

["fixgoto"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Assister") < 30,"fast") or bufcnt(true,20) then
      return "dfpassball"
  -- elseif  bufcnt(true, 200) then
   --   return "exit"
    end
  end,
  Middle   = task.goCmuRush(MASK_POS),
  Special  = task.goCmuRush(INNER_POS,player.toBallDir("Special")),
  Leader   = task.goCmuRush(MAKE_POS, player.toBallDir("Leader")),
  Defender = task.goCmuRush(READY_POS, player.toBallDir("Defender")),
  Assister = task.goCmuRush(SHOOT_POS3, player.toBallDir("Assister")),
  Goalie   = task.goalie(),
  match    = "{ALDSM}"
},

["dfpassball"] = {
  switch = function ()  
    if  player.kickBall("Defender") or
      (( math.abs(ball.velDir()-player.toBallDir("Defender")) < math.pi/18) and (ball.velMod() > 80)) then
      return "gokick"
   -- elseif  bufcnt(true, 120) then
   --   return "exit"
    end
  end,
  Middle   = task.rightBack(),
  Special  = task.goCmuRush(INNER_POS,player.toBallDir),
  Leader   = task.leftBack(),
  --Leader   = task.goCmuRush(MAKE_POS, player.toBallDir),
  Defender = task.receivePass("Assister",400),
  Assister = task.goCmuRush(SHOOT_POS3, player.toBallDir),
  Goalie   = task.goalie(),
  match    = "{D}{AS}{LM}"
},

["gokick"] = {
    switch = function ()
    if player.kickBall("Assister") then
      return "exit"
    elseif  bufcnt(true, 480) then
      return "exit"
    end
  end,
  Assister = task.receiveShoot(),
  Middle   = task.rightBack(),
  Defender  = task.defendMiddle(),
  Special  = task.goCmuRush(MASK_POS,player.toBallDir("Special")),
  Leader = task.leftBack(),
  Goalie   = task.goalie(),
  match    = "{A}{S}{DLM}"
},

name = "Ref_FrontKickV61",
applicable ={
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
