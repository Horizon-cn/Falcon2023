local START_POS = CGeoPoint:new_local(27/1200*param.pitchLength,0)
local RECEIVE_POS_1 = CGeoPoint:new_local(-110/1200*param.pitchLength,-70/900*param.pitchWidth)
local RECEIVE_POS_2 = CGeoPoint:new_local(-110/1200*param.pitchLength,70/900*param.pitchWidth)

local SwitchBallArea = function()
  if cond.isGameOn() then
    return "exit"
  elseif math.abs(ball.posX())<15 and math.abs(ball.posY())<15 then
    return "kickoff1"
  elseif (ball.posY()<-220 or ball.posY()>220) and ball.posX()<-200 then
    return "StopCornerDef"
  elseif ball.posY()>-220 and ball.posY()<220 and ball.posX()<-200 then
    return "StopBackDef"
  elseif ball.posX()>-200 and ball.posX()<200 then
    return "StopMiddleDef"
  elseif ball.posX()>200 then
    return "StopFrontDef"
  else
    return "exit"
  end
end

gPlayTable.CreatePlay{
  firstState = "StopBackDef",

  ["kickoff1"]= {
    switch = SwitchBallArea,
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

  ["StopCornerDef"]= {
    --MultiDefend
    switch = SwitchBallArea,
    Leader = task.defendKick(),
    Assister = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.multiBack(3,3),
    Defender = task.sideBack(),
    Crosser  = task.markingFront("First"),
    Breaker  = task.support("Leader",4),
    Goalie = task.goalieNew(),
    match = "[AM][L][DS][C][B]"
},

  ["StopBackDef"]= {
    --MultiDefend
    switch = SwitchBallArea,
    Leader = task.defendKick(),
    Assister = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.multiBack(3,3),
    Defender = task.sideBack(),
    Crosser  = task.markingFront("First"),
    Breaker  = task.support("Leader",4),
    Goalie = task.goalieNew(),
    match = "[AM][L][DS][C][B]"
},

  ["StopMiddleDef"]= {
    --MiddleDefendBalance
    switch = SwitchBallArea,
    Leader = task.defendKick(),
    Assister = task.support("Leader",2),
    Middle = task.sideBack(), 
    Special = task.markingFront("First"),
    Defender = task.multiBack(3,1),
    Crosser  = task.multiBack(3,2), 
    Breaker  = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[DC][M][L][B][S][A]"
},

  ["StopFrontDef"]= {
    --MiddleAttack
    switch = SwitchBallArea,
    Leader = task.defendKick(),
    Assister = task.support("Leader",2),
    Middle =  task.markingFront("First"),
    Special = task.markingFront("Second"),
    Defender = task.multiBack(3,1),
    Crosser  = task.multiBack(3,2),
    Breaker  = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[DC][L][B][MS][A]"
},

  name = "Ref_StopV2_Play8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}