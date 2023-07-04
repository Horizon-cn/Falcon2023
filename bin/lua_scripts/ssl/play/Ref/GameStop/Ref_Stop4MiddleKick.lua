-- 角球定位球在一开始就进行站位
-- by zhyaic 2014-04-08
-- yys 2015-06-10
local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end
local BLOCK_POS = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local(ball.posX(),350))()
  else
    return ball.syntYPos(CGeoPoint:new_local(ball.posX(),200))()
  end
end
local BARYCENTER = function()
  if math.abs(ball.posY()) < 250 then
    return ball.syntYPos(CGeoPoint:new_local((550+ball.posX())/2,235))()
  else
    return ball.syntYPos(CGeoPoint:new_local((560+ball.posX())/2,250))() 
  end
end

gPlayTable.CreatePlay{
 
firstState = "start",

["start"] = {
  switch = function()
    if cond.isGameOn() then
      return "exit"
    end
  end,
  Assister = task.goCmuRush(WAIT_BALL_POS,player.toBallDir,_,flag.allow_dss + flag.dodge_ball),
  Leader   = task.goCmuRush(BARYCENTER, player.toBallDir,_,flag.allow_dss + flag.dodge_ball),
  -- Middle   = task.multiBack(3,1),
  Middle   = task.stop(),
  Special  = task.goCmuRush(BLOCK_POS,player.toBallDir,_,flag.allow_dss + flag.dodge_ball),
  -- Defender = task.multiBack(3,2),
  -- Breaker  = task.multiBack(3,3),
  Defender  = task.stop(),
  Breaker = task.stop(),
  Crosser  = task.stop(),
  -- sideBack(),
  Goalie   = task.goalieNew(),
  --match    = "[D][B][A][C][L][S][M]"
  match    = "[A][L][S][B][C][D][M]"
},

name = "Ref_Stop4MiddleKick",
applicable = {
  exp = "a",
  a = trued
},
attribute = "attack",
timeout = 99999
}