local STOP_POS = function()
  return ball.pos() + Utils.Polar2Vector(65, ball.toOurGoalDir())
end
gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.goCmuRush(STOP_POS, player.toBallDir, _, flag.slowly),
  Assister = task.defendHead(),
  Special = task.marking("First"),
  Middle = task.leftBack(),
  Defender = task.rightBack(),
  Goalie = task.goalieNew(),
  match    = "[L][MD][SA]"
},
  name = "Ref_CornerDefV20",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}