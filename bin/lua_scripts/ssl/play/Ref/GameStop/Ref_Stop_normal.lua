local START_POS = CGeoPoint:new_local(27/1200*param.pitchLength,0)
local RECEIVE_POS_1 = CGeoPoint:new_local(-110/1200*param.pitchLength,-70/900*param.pitchWidth)
local RECEIVE_POS_2 = CGeoPoint:new_local(-110/1200*param.pitchLength,70/900*param.pitchWidth)

local SwitchBallArea = function()
  if cond.isGameOn() then
    return "exit"
  elseif math.abs(ball.posX())<15 and math.abs(ball.posY())<15 then
    return "kickoff1"
  elseif ball.posX() > 480 and math.abs(ball.posY()) > 300 then --我方CornerKick
    return "CornerKickStop"
  elseif ball.posX() > 100 then --我方FrontKick
    return "FrontKickStop"
  elseif ball.posX() > -100 then --半攻半防
    return "MiddleStop"
  elseif ball.posX() < -300 and math.abs(ball.posY()) > 120  then 
    return "CornerDefendStop"
  elseif ball.posX() < -300 and math.abs(ball.posY()) < 120 then
    return "BackDefendStop"
  else
    return "BackDefendStop"
  end
end
------------------------
--CornerKickStop FrontKickStop
local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(70, ball.antiY()*math.pi)
end
local KICK_DIR  = ball.antiYDir(1.57)
local FRONT_POS1= ball.antiYPos(CGeoPoint:new_local(350/1200*param.pitchLength,-150/900*param.pitchWidth))
local FRONT_POS2= ball.antiYPos(CGeoPoint:new_local(260/1200*param.pitchLength,0/900*param.pitchWidth))
local FRONT_POS3= ball.antiYPos(CGeoPoint:new_local(370/1200*param.pitchLength,210/900*param.pitchWidth))
local ACC=500;
------------------------
--MiddleStop
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
------------------------
local DefendMiddlePos = CGeoPoint:new_local(-450/1200*param.pitchLength,0)
------------------------

gPlayTable.CreatePlay{
  firstState = "BackDefendStop",

["kickoff1"]= {
  switch   = SwitchBallArea,
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

["CornerKickStop"]= {
  switch   = SwitchBallArea,
  Assister = task.goCmuRush(WAIT_BALL_POS,player.toPointDir(SHOOT_POS), ACC, flag.allow_dss + flag.dodge_ball),
  Leader   = task.goCmuRush(FRONT_POS3, player.toPlayerHeadDir("Assister"), ACC, flag.allow_dss + flag.dodge_ball),
  Middle   = task.goCmuRush(FRONT_POS1, player.toPlayerHeadDir("Assister"), ACC, flag.allow_dss + flag.dodge_ball),
  Special  = task.sideBack(),
  Defender = task.multiBack(3,1),
  Breaker  = task.multiBack(3,2),
  Crosser  = task.multiBack(3,3),
  Goalie   = task.goalieNew(),
  match    = "[D][A][L][B][C][M][S]"
--match    = "[D][A][L][B][C][M][S]"
},

["FrontKickStop"]= {
  switch   = SwitchBallArea,
  Assister = task.goCmuRush(WAIT_BALL_POS,player.toPointDir(SHOOT_POS), ACC, flag.allow_dss + flag.dodge_ball),
  Leader   = task.goCmuRush(FRONT_POS3, player.toPlayerHeadDir("Assister"), ACC, flag.allow_dss + flag.dodge_ball),
  Middle   = task.goCmuRush(FRONT_POS1, player.toPlayerHeadDir("Assister"), ACC, flag.allow_dss + flag.dodge_ball),
  Special  = task.sideBack(),
  Defender = task.multiBack(3,1),
  Breaker  = task.multiBack(3,2),
  Crosser  = task.multiBack(3,3),
  Goalie   = task.goalieNew(),
  match    = "[D][A][L][BC][M][S]"
},

--接Ref_MiddleDef_Normal
["MiddleStop"]= {
  switch   = SwitchBallArea,
  Leader = task.defendKick(),
    Assister =task.sideBack(),
    Middle = task.support("Leader", DetectTheSupportID),
    Special = task.defendMiddle(),-- sideBackUltra
    Defender = task.leftBack(), 
    Crosser  = task.rightBack(), 
    Breaker  = task.sideBackUltra(),--task.markingFront("First"),
    Goalie = task.goalieNew(),
  match    = "[L][DC][S][M][B][A]"
},

["CornerDefendStop"]= {
  switch   = SwitchBallArea,
  Leader   = task.defendMiddle(),
  Assister = task.goCmuRush(DefendMiddlePos,player.toPointDir(SHOOT_POS),ACC,flag.allow_dss + flag.dodge_ball),
  Middle   = task.sideBack(),
  Special  = task.support("Leader",DetectTheSupportID), 
  Defender = task.leftBack(),
  Crosser  = task.rightBack(),
  Breaker  = task.sideBackUltra(),
  Goalie   = task.goalieNew(),
  --match    = "[L][DC][S][M][A][B]"
  -- match    = "[L][M][D][S][C][A][B]"
  match    = "[L][M][D][S][A][C][B]"
},  

["BackDefendStop"]= {
  switch   = SwitchBallArea,
  Leader   = task.defendKick(),
  Assister = task.multiBack(1,1),
  Middle   = task.sideBack(),
  Special  = task.support("Leader",DetectTheSupportID), 
  Defender = task.leftBack(),
  Crosser  = task.rightBack(),
  Breaker  = task.sideBackUltra(),
  Goalie   = task.goalieNew(),
  match    = "[L][DC][S][A][B][M]"
},  

  name = "Ref_Stop_normal",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}