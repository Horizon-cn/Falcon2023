local STOP_FLAG  = bit:_or(flag.slowly, flag.dodge_ball)
local STOP_DSS   = bit:_or(STOP_FLAG, flag.allow_dss)

local DEFX = -(param.pitchLength/2 - param.penaltyDepth -3 * param.playerRadius)
local DEFY = param.penaltyWidth/2 + 2 * param.playerRadius 

local DEF_POS1 = ball.syntYPos(CGeoPoint:new_local(-293, 46))
local DEF_POS2 = ball.syntYPos(CGeoPoint:new_local(DEFX, DEFY + 3 * param.playerRadius))
local DEF_POS3 = ball.antiYPos(CGeoPoint:new_local(DEFX, DEFY))
local WAIT_BALL_POS = function ()
  return ball.pos() + Utils.Polar2Vector(-50, ball.syntY(0.2 * math.pi))
end
gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.multiBack(4,1),
  Middle = task.multiBack(4,2),
  Defender = task.multiBack(4,3),
  Special = task.multiBack(4,4),
  Assister = task.marking("First"),
  Breaker = task.marking("Second"),
  Crosser = task.goCmuRush(WAIT_BALL_POS,_,_,flag.allow_dss + flag.dodge_ball),
  Goalie = task.goalieNew(),
  match    = "[M][C][DLS][AB]"
},
  name = "Ref_FrontDef8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}