local WAIT_BALL_POS = function ()
  return ball.pos() + Utils.Polar2Vector(-50, ball.syntY(0.2 * math.pi))
end
local SHOOT_POS = ball.antiYPos(CGeoPoint:new_local(0/1200*param.pitchLength,0/900*param.pitchWidth))

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.multiBack(2,1),
  Middle = task.multiBack(2,2),
  Defender = task.defendKick(),
  Special = task.sideBack(),
  Assister = task.markingFront("First"),
  Breaker =task.markingFront("Second"),
  Crosser = task.goCmuRush(WAIT_BALL_POS,player.toPointDir(SHOOT_POS),_,flag.allow_dss + flag.dodge_ball),
  Goalie = task.goalieNew(),
  match    = "[LM][DS][ABC]"
},
  name = "Ref_BackDef_PureDefence8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}