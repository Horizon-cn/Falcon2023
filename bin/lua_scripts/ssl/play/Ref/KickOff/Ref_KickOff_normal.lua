local START_POS = CGeoPoint:new_local(27/1200*param.pitchLength,0)
local START_POS_1 = CGeoPoint:new_local(27/1200*param.pitchLength,18/900*param.pitchWidth)
local START_POS_2 = CGeoPoint:new_local(27/1200*param.pitchLength,-18/900*param.pitchWidth)
local RECEIVE_POS_1 = CGeoPoint:new_local(-110/1200*param.pitchLength,-70/900*param.pitchWidth)
local RECEIVE_POS_2 = CGeoPoint:new_local(-110/1200*param.pitchLength,70/900*param.pitchWidth)
local GetBallPos = pos.passForTouch(RECEIVE_POS_1)

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
  match    = "[L][A][S][MDBC]"
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
  match    = "[L][A][S][MDBC]"
},

["receive1"] = {
  switch = function ()
    if bufcnt(player.toBallDist("Assister") < 20, 20, 150) then
      return "exit"
    end
  end,
  Leader   = task.support("Assister",4),
  Assister = task.receive("Leader",RECEIVE_POS_1),
  Special  = task.support("Assister",4),--todo 待定
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[A][SL][MDBC]"
},

["receive2"] = {
  switch = function ()
    if bufcnt(player.toBallDist("Special") < 20, 20, 150) then
      return "exit"
    end
  end,
  Leader   = task.support("Special",4),
  Assister  = task.support("Special",4),--todo 待定
  Special = task.receive("Leader",RECEIVE_POS_2),
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[S][AL][MDBC]"
},


name = "Ref_KickOff_normal",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
