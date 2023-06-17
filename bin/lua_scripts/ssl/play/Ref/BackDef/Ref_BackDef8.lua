gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.defendKick(),
  Middle = task.leftBack(),
  Defender = task.rightBack(),
  Special = task.sideBack(),
  Assister = task.markingFront("First"),
  Goalie = task.goalieNew(),
  match    = "[L][MD][A][S]"
},
  name = "Ref_BackDef8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}