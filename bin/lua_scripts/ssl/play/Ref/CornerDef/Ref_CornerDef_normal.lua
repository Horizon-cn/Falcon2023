gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.defendMiddle(),
  Assister = task.defendHead(),
  Special = task.markingFront("First"),
  Breaker = task.markingFront("Second"),
  Crosser = task.markingFront("Third"),
  Middle = task.leftBack(),
  Defender = task.rightBack(),
  Goalie = task.goalieNew(),
  match    = "[MD][AL][SBC]"
},
  name = "Ref_CornerDef_normal",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}