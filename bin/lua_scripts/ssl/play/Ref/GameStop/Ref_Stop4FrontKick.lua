-- 角球定位球在一开始就进行站位
-- by zhyaic 2014-04-08
-- yys 2015-06-10

local STOP_FLAG  = bit:_or(flag.slowly, flag.dodge_ball)
local STOP_DSS   = bit:_or(flag.dodge_ball, flag.allow_dss)
local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(60, ball.antiY()*math.pi)
end

local FRONT_POS1= ball.antiYPos(CGeoPoint:new_local(350/1200*param.pitchLength,-150/900*param.pitchWidth))
local FRONT_POS2= ball.antiYPos(CGeoPoint:new_local(260/1200*param.pitchLength,0/900*param.pitchWidth))
local FRONT_POS3= ball.antiYPos(CGeoPoint:new_local(370/1200*param.pitchLength,210/900*param.pitchWidth))
local ACC=500;
local SHOOT_POS = ball.antiYPos(CGeoPoint:new_local(380/1200*param.pitchLength,150/900*param.pitchWidth))

gPlayTable.CreatePlay{
 
firstState = "start",

["start"] = {
  switch = function()
    if cond.isGameOn() then
      return "exit"
    end   
  end,
  Assister = task.goCmuRush(WAIT_BALL_POS,player.toPointDir(SHOOT_POS), ACC, flag.allow_dss + flag.dodge_ball),
  Leader   = task.goCmuRush(FRONT_POS3, player.toPlayerHeadDir("Assister"), ACC, flag.allow_dss + flag.dodge_ball),
  Middle   = task.goCmuRush(FRONT_POS1, player.toPlayerHeadDir("Assister"), ACC, flag.allow_dss + flag.dodge_ball),
  Special  = task.sideBack(),
  Defender = task.multiBack(3,1),
  Breaker  = task.multiBack(3,2),
  Crosser  = task.multiBack(3,3),
  Goalie   = task.goalieNew(),
  match    = "[D][B][A][C][L][M][S]"
},

name = "Ref_Stop4FrontKick",
applicable = {
  exp = "a",
  a = trued
},
attribute = "attack",
timeout = 99999
}