-- 球在前场中侧的停球站位，尽量分散，避免跑位过程中撞到球
-- by HeJiaping 2020-11-09


local STOP_FLAG  = bit:_or(flag.slowly, flag.dodge_ball)
local STOP_DSS   = bit:_or(STOP_FLAG, flag.allow_dss)

local DEFX = -(param.pitchLength/2 - param.penaltyDepth -3 * param.playerRadius)
local DEFY = param.penaltyWidth/2 + 2 * param.playerRadius 

local DEF_POS1 = ball.syntYPos(CGeoPoint:new_local(DEFX, DEFY))
local DEF_POS2 = ball.syntYPos(CGeoPoint:new_local(DEFX, DEFY + 3 * param.playerRadius))
local DEF_POS3 = ball.antiYPos(CGeoPoint:new_local(DEFX, DEFY))

local ACC = 300

gPlayTable.CreatePlay{

firstState = "start",

["start"] = {
  switch = function()
    if cond.isGameOn() then
      return "exit"
    end   
  end,
  Defender = task.goCmuRush(DEF_POS1, _,  ACC, STOP_DSS),
  Middle  = task.goCmuRush(DEF_POS2, _,  ACC, STOP_DSS),
  Special  = task.goCmuRush(DEF_POS3, _,  ACC, STOP_DSS),
  Leader   = task.leftBack(),
  Assister = task.rightBack(),
  Goalie   = task.goalieNew(),
  match    = "[LA][MSD]"
},

name = "Ref0_StopV3",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}