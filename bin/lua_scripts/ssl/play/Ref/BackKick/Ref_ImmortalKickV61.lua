--欺骗策略
local halfPitchX = param.pitchLength/2    -- 半场长度
local halfPitchY = param.pitchWidth/2   -- 半场宽度
local halfGoalW = param.goalWidth/2

local cheatshootpos = ball.refAntiYPos(CGeoPoint:new_local(170,-70))
local CHEAT = pos.passForTouch(ball.refAntiYPos(CGeoPoint:new_local(170,-70)))

local MAKE_POS_ORG    = CGeoPoint:new_local(100, -250)
local RIGHT_POS   = ball.refSyntYPos(CGeoPoint:new_local(280, 220))
local INNER_POS   = ball.refSyntYPos(CGeoPoint:new_local(350, 220))
local RIGHT_POS2  = ball.refSyntYPos(CGeoPoint:new_local(250, 250))
local MAKE_POS    = ball.refAntiYPos(MAKE_POS_ORG)
local READY_POS   = ball.refSyntYPos(CGeoPoint:new_local(80, -150))
local SHOOT_POS   = ball.refSyntYPos(CGeoPoint:new_local(340, -200))
local MASK_POS    = ball.refSyntYPos(CGeoPoint:new_local(320, 100))
local SHOOT_POS2  = ball.refSyntYPos(CGeoPoint:new_local(280, -130))
local SHOOT_POS3  = ball.refSyntYPos(CGeoPoint:new_local(50, 100))
local GOALIE_POS = {
  ball.refSyntYPos(CGeoPoint:new_local(-0.5*halfPitchX,0.3*halfPitchY)),
  ball.refSyntYPos(CGeoPoint:new_local(-0.3*halfPitchX,0.3*halfPitchY)),
  ball.refSyntYPos(CGeoPoint:new_local(0.1*halfPitchX,0.3*halfPitchY)),
  FINAL_SHOOT_POS,
}
local function def_chipPower()
  if math.abs(ball.posY()) > 270 then 
    return 250
  else 
    return 200
  end
end
local SPECIAL_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(270,240)),
  ball.refAntiYPos(CGeoPoint:new_local(0.75*halfPitchX,0.75*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.8*halfPitchX,0.95*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.9*halfPitchX,0.95*halfPitchY)),
}
local LEADER_POS = {
ball.refAntiYPos(CGeoPoint:new_local(-85,-50)),
ball.refAntiYPos(CGeoPoint:new_local(-100,0)),
ball.refAntiYPos(CGeoPoint:new_local(-85,50)),
ball.refAntiYPos(CGeoPoint:new_local(-85,0)),
}
local MIDDLE_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(270,215)),
  ball.refAntiYPos(CGeoPoint:new_local(340,215)),
  ball.refAntiYPos(CGeoPoint:new_local(335,115)),
  ball.refAntiYPos(CGeoPoint:new_local(380,220)),

}
local DEFENDER_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(0.45*halfPitchX,0.45*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.2*halfPitchX,0.95*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.7*halfPitchX,0.95*halfPitchY)),
}
local function projectX()
    local x = 0
    if(ball.posY()>0) then --170 -70
         if(ball.posX()>=170) then
            x = 16
            return x
         else
           x = -16
            return x 
         end
    else --170 70
          if(ball.posX()>=170) then
            x = 16
            return x
          else
           x = -16
            return x
          end
    end
end

local function projectY()
    local y = 0
    if(ball.posY()>0) then --170 -70
         if(ball.posX()>=170) then
            y = 16
            return y
         else
           y = 16
            return y
         end
    else --170 70
          if(ball.posX()>=170) then
            y = -16
            return y
          else
           y = -16
            return y
          end
    end
end

gPlayTable.CreatePlay{


firstState = "getready",
--各就各位，Middle去球门前干扰，special协同干扰，在chippass之后回防，Leader在中场待命，由Leader完成最终kick，
--Assister负责传球，Defender始终作为诱饵
["getready"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Defender")<30
    , "normal") then
      return "startball"
    end
  end,
  --Assister = task.goCmuRush(ball.pos())
  Assister = task.goCmuRush(pos.reflectPos(projectX(),-projectY()) ),
  Leader   = task.goCmuRush(LEADER_POS[1]),
  Special  = task.goCmuRush(SPECIAL_POS[1]),
 Defender = task.goCmuRush(READY_POS),
  Middle   = task.goCmuRush(MIDDLE_POS[3]),
  Goalie   = task.goalie(),
  match    = "{A}{M}{DLS}"
},

["startball"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Defender")<30 and
      player.toTargetDist("Middle")<30 and 
      player.toTargetDist("Assister")<10 , 10, 180)  then
      return "getball"
    end
  end,
  Assister = task.staticGetBall(CHEAT),
  Middle   = task.runMultiPos(MIDDLE_POS),
  Special  = task.goCmuRush(SPECIAL_POS[1]),
  Leader   = task.goCmuRush(LEADER_POS[1]),
  Defender = task.goCmuRush(READY_POS),
  Goalie   = task.goalie(),
  match    = "{A}{M}{D}{SL}"
},

["getball"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Assister")<20, "fast", 100) then
      return "chippass"
    end
  end,
  Assister = task.staticGetBall(CHEAT),
  Middle   = task.runMultiPos(MIDDLE_POS),
  Special  = task.goCmuRush(SPECIAL_POS[1]),
  Leader   = task.goCmuRush(cheatshootpos, dir.compensate(CHEAT), 300),
  Defender = task.goCmuRush(READY_POS, player.toBallDir("Defender")),
  Goalie   = task.goalie(),
  match    = "{ADLSM}"
},

["chippass"] = {
  switch = function ()
    if bufcnt( player.kickBall("Assister") or
      player.toBallDist("Assister")>20,"fast", 100)  then
      return "exit"
    end
  end,
  Assister = task.chipPass(CHEAT(),def_chipPower()),
  Middle   = task.runMultiPos(MIDDLE_POS),
  Special  = task.singleBack(),
  Leader   = task.goCmuRush(cheatshootpos, dir.compensate(CHEAT), 300),
  Defender = task.goCmuRush(READY_POS,player.toBallDir("Defender")),
  Goalie   = task.goalie(),
  match    = "{ADLSM}"
},


name = "Ref_ImmortalKickV61",
applicable ={
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
