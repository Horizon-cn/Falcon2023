local STOP_FLAG  = bit:_or(flag.slowly, flag.dodge_ball)
local STOP_DSS   = bit:_or(STOP_FLAG, flag.allow_dss)

local DEFX = -(param.pitchLength/2 - param.penaltyDepth -3 * param.playerRadius)
local DEFY = param.penaltyWidth/2 + 2 * param.playerRadius 

local DEF_POS1 = ball.syntYPos(CGeoPoint:new_local(-293/1200*param.pitchLength,46/900*param.pitchWidth))
local DEF_POS2 = ball.syntYPos(CGeoPoint:new_local(DEFX, DEFY + 3 * param.playerRadius))
local DEF_POS3 = ball.antiYPos(CGeoPoint:new_local(DEFX, DEFY))
local WAIT_BALL_POS = function ()
  return ball.pos() + Utils.Polar2Vector(-50, ball.syntY(0.2 * math.pi))
end
local SHOOT_POS = ball.syntYPos(CGeoPoint:new_local(500/1200*param.pitchLength,0/900*param.pitchWidth))

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.multiBack(3,1),
  Middle = task.multiBack(3,2),
  Defender = task.multiBack(3,3),
  Special = task.defendKick(),
  Assister = task.markingFront("First"),
  Breaker = task.markingFront("Second"),
  Crosser = task.goCmuRush(WAIT_BALL_POS,player.toPointDir(SHOOT_POS),_,flag.allow_dss + flag.dodge_ball),
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