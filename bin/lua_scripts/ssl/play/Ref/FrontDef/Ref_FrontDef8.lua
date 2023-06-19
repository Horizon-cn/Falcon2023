local STOP_FLAG  = bit:_or(flag.slowly, flag.dodge_ball)
local STOP_DSS   = bit:_or(STOP_FLAG, flag.allow_dss)

local DEFX = -(param.pitchLength/2 - param.penaltyDepth -3 * param.playerRadius)
local DEFY = param.penaltyWidth/2 + 2 * param.playerRadius 

local DEF_POS1 = ball.syntYPos(CGeoPoint:new_local(-293, 46))
local DEF_POS2 = ball.syntYPos(CGeoPoint:new_local(DEFX, DEFY + 3 * param.playerRadius))
local DEF_POS3 = ball.antiYPos(CGeoPoint:new_local(DEFX, DEFY))

local ACC = 300
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
  Crosser = task.marking("Third"),
  Goalie = task.goalieNew(),
  match    = "[MDLS][ABC]"
},
  name = "Ref_FrontDef8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}