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
  Leader = task.multiBack(3,1),
  Middle = task.multiBack(3,2),
  Defender = task.multiBack(3,3),
  Special = task.sideBack(),
  Assister = task.markingFront("First"),
  Breaker =task.markingFront("Second"),
  Crosser = task.task.goCmuRush(WAIT_BALL_POS,_,_,flag.allow_dss + flag.dodge_ball),
  Goalie = task.goalieNew(),
  match    = "[LM][DS][ABC]"
},
  name = "Ref_BackDef8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}