
gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.defendKick(),
  Assister = task.marking("Third"),
  --Assister = task.goMMPassPos("Leader"),
  Powerhouse = task.marking("Second"),
  Special = task.multiBack(3, 1), --sideBack(),
  Defender = task.marking("First"),
  Hawk = task.multiBack(3,2), --leftBack(),
  Middle = task.multiBack(3, 3), --rightBack(),
  Goalie = task.goalieNew(),
    match = "[L][A][PSDHM]"
},
  name = "Ref_BackDefV12",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}