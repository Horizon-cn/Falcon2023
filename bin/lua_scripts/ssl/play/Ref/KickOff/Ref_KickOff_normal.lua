local START_POS = CGeoPoint:new_local(27/1200*param.pitchLength,0)
local START_POS_1 = CGeoPoint:new_local(27/1200*param.pitchLength,18/900*param.pitchWidth)
local START_POS_2 = CGeoPoint:new_local(27/1200*param.pitchLength,-18/900*param.pitchWidth)
local RECEIVE_POS_1 = CGeoPoint:new_local(-110/1200*param.pitchLength,-70/900*param.pitchWidth)
local RECEIVE_POS_2 = CGeoPoint:new_local(-110/1200*param.pitchLength,70/900*param.pitchWidth)
local GetBallPos = pos.passForTouch(RECEIVE_POS_1)

local DetectTheSupportID = function() 
    if ball.posX() > 200 and ball.posY() < -120 then  -- 在0号区域
        return 2  -- 往2号区域打
    elseif ball.posX() > 200 and ball.posY() < 120 then -- 在1号区域
        if ball.posX() > 0 then
            return 2
        else 
            return 0
        end
    elseif ball.posX() > 200 and ball.posY() >= 120 then -- 在2号区域
        return 0 -- 往0号打
    elseif ball.posX() > -200 and ball.posY() < -120 then -- 在3号区域
        return 0 -- 往0号打
    elseif ball.posX() > -200 and ball.posY() < 120 then -- 在4号区域
        return 1 -- 往1号打
    elseif ball.posX() > -200 and ball.posY() >= 120 then -- 在5号区域
        return 2 -- 往2号打
    else
        return 4 -- 往4号打
    end
end

local receive_dir = function(num)
  return (player.pos(gRoleNum["Leader"]) - player.pos(num)):dir()
end

gPlayTable.CreatePlay{
firstState = "start",

["start"] = {
  switch = function ()
    if cond.isNormalStart() then
      if ball.posY()<0 then
        return "adjust1"
      else
        return "adjust2"
      end
    end
  end,
  Leader   = task.goCmuRush(START_POS,math.pi,_,flag.allow_dss),
  Assister = task.goCmuRush(RECEIVE_POS_1,receive_dir,_,flag.allow_dss),
  Special  = task.goCmuRush(RECEIVE_POS_2,receive_dir,_,flag.allow_dss),
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[L][A][S][MDBC]"
},

["adjust1"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Leader")<10,5,100) then
      return "getball1"
    end
  end,
  Leader   = task.goCmuRush(START_POS_1,player.toBallDir,_,flag.allow_dss),
  Assister = task.goCmuRush(RECEIVE_POS_1,receive_dir,_,flag.allow_dss),
  Special  = task.goCmuRush(RECEIVE_POS_2,receive_dir,_,flag.allow_dss),
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[L][A][S][MDBC]"
},

["adjust2"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Leader")<10,5,100) then
      return "getball2"
    end
  end,
  Leader   = task.goCmuRush(START_POS_2,player.toBallDir,_,flag.allow_dss),
  Assister = task.goCmuRush(RECEIVE_POS_1,receive_dir,_,flag.allow_dss),
  Special  = task.goCmuRush(RECEIVE_POS_2,receive_dir,_,flag.allow_dss),
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[L][A][S][MDBC]"
},

["getball1"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Leader")<20 ,70,100)  then
      return "kickoftoA" -- y>0 getball is correct
    end
  end,
  Leader   = task.staticGetBall(GetBallPos),
  Assister = task.goCmuRush(RECEIVE_POS_1,receive_dir,_,flag.allow_dss),
  Special  = task.goCmuRush(RECEIVE_POS_2,receive_dir,_,flag.allow_dss),
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[L][A][S][MDBC]"
},

["getball2"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Leader")<20 ,70,100)  then
      return "kickoftoS"
    end
  end,
  Leader   = task.staticGetBall(GetBallPos),
  Assister = task.goCmuRush(RECEIVE_POS_1,receive_dir,_,flag.allow_dss),
  Special  = task.goCmuRush(RECEIVE_POS_2,receive_dir,_,flag.allow_dss),
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[L][S][A][MDBC]"
},



["kickoftoA"] = {
    switch = function ()
    if bufcnt(player.kickBall("Leader"), "fast", 200) then
      -- if bufcnt(player.toBallDist("Leader") > 30) then
      return "receive1"
    end
  end,
  Leader   = task.passToPos(RECEIVE_POS_1,250,pre.middlehigh),
  Assister = task.goCmuRush(RECEIVE_POS_1,receive_dir,_,flag.allow_dss),
  Special  = task.goCmuRush(RECEIVE_POS_2,receive_dir,_,flag.allow_dss),
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[L][A][S][MDBC]"
},

["kickoftoS"] = {
    switch = function ()
    if bufcnt(player.kickBall("Leader"), "fast", 200) then
      -- if bufcnt(player.toBallDist("Leader") > 30) then
      return "receive2"
    end
  end,
  Leader   = task.passToPos(RECEIVE_POS_2,250,pre.middlehigh),
  Assister = task.goCmuRush(RECEIVE_POS_1,receive_dir,_,flag.allow_dss),
  Special  = task.goCmuRush(RECEIVE_POS_2,receive_dir,_,flag.allow_dss),
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[L][S][A][MDBC]"
},

["receive1"] = {
  switch = function ()
    if bufcnt(ball.toPlayerHeadDist("Assister") < 20, 10, 150) then
      return "exit"
    end
  end,
  Leader   = task.support("Assister",DetectTheSupportID),
  Assister = task.receive("Leader",RECEIVE_POS_1),
  Special  = task.protectBall(),  --todo 待定
  Middle   = task.multiBack(3,1),
  Defender = task.multiBack(3,2),
  Breaker  = task.multiBack(3,3),
  Crosser  = task.markingFront("First"),
  Goalie   = task.goalieNew(),
  match    = "[A][L][MD][S][B][C]"
},

["receive2"] = {
  switch = function ()
    if bufcnt(player.toBallDist("Special") < 20, 10, 150) then
      return "exit"
    end
  end,
  Leader   = task.support("Special",DetectTheSupportID),
  Assister  = task.protectBall(),  --todo 待定
  Special = task.receive("Leader",RECEIVE_POS_2),
  Middle   = task.multiBack(3,1),
  Defender = task.multiBack(3,2),
  Breaker  = task.multiBack(3,3),
  Crosser  = task.markingFront("First"),
  Goalie   = task.goalieNew(),
  match    = "[A][L][MD][S][B][C]"
},


name = "Ref_KickOff_normal",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
