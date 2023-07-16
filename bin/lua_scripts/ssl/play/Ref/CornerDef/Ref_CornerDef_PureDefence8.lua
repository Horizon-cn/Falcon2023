local SHOOT_POS = ball.syntYPos(CGeoPoint:new_local(520/1200*param.pitchLength,0/900*param.pitchWidth))
local WAIT_BALL_POS = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.2 * math.pi))
end
gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.multiBack(1,3),
  Assister = task.defendKick(),
  Special = task.markingFront("First"),
  Breaker = task.markingFront("Second"),
  Crosser = task.goCmuRush(WAIT_BALL_POS,player.toPointDir(SHOOT_POS),_,flag.allow_dss + flag.dodge_ball),
  Middle = task.multiBack(2,3),
  Defender = task.multiBack(3,3),
  Goalie = task.goalieNew(),
  match    = "[MD][AL][SBC]"
},
  name = "Ref_CornerDef_PureDefence8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}