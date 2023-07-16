local START_POS = CGeoPoint:new_local(-35/1200*param.pitchLength,0/900*param.pitchWidth)
local RECEIVE_POS_1 = CGeoPoint:new_local(-110/1200*param.pitchLength,-70/900*param.pitchWidth)
local RECEIVE_POS_2 = CGeoPoint:new_local(-110/1200*param.pitchLength,70/900*param.pitchWidth)
local CHIP_POS = CGeoPoint:new_local(530/1200*param.pitchLength,0/900*param.pitchWidth)
local kickPower = 400

gPlayTable.CreatePlay{
firstState = "start",

["start"] = {
  switch = function ()
    if cond.isNormalStart() then
      return "kickof"
    end
  end,
  Leader   = task.goCmuRush(START_POS,_,_,flag.allow_dss),
  Assister = task.goCmuRush(RECEIVE_POS_1,-3,_,flag.allow_dss),
  Special  = task.goCmuRush(RECEIVE_POS_2,-3,_,flag.allow_dss),
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[L][A][S][MDBC]"
},

["kickof"] = {
    switch = function ()
    --if bufcnt(player.kickBall("Leader"), "fast", 200) then
      if bufcnt(player.toBallDist("Leader") > 30) then
      return "receive"
    end
  end,
  Leader   = task.chipPass(CHIP_POS,kickPower),
  Assister = task.goCmuRush(RECEIVE_POS_1,-3,_,flag.allow_dss),
  Special  = task.goCmuRush(RECEIVE_POS_2,-3,_,flag.allow_dss),
  Middle   = task.multiBack(4,1),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[L][A][S][MDBC]"
},

["receive"] = {
  switch = function ()
    if bufcnt(player.toBallDist("Assister") < 20, 20, 150) then
      return "exit"
    end
  end,
  Leader   = task.multiBack(4,1),
  Assister = task.receive("Leader"),
  Special  = task.leftBack(),
  Middle   = task.rightBack(),
  Defender = task.multiBack(4,2),
  Breaker  = task.multiBack(4,3),
  Crosser  = task.multiBack(4,4),
  Goalie   = task.goalieNew(),
  match    = "[A][SM][LDBC]"
},


name = "Ref_KickOff_PureDefence8",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
