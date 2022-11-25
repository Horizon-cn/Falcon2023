gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.defendKick(),
  Assister = task.goMMPassPos("Leader"),
  Powerhouse = task.marking("Third"),
  Special = task.marking("Second"),
  Defender = task.marking("First"),
  Hawk = task.leftBack(),
  Middle = task.rightBack(),
  Goalie = task.goalieNew(),
    match = "[L][APSD][HM]"
},
  name = "Ref_FrontDefV9",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}