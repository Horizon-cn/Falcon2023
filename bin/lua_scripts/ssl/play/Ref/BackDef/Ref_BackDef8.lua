gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.rightBack(),
  Middle = task.leftBack(),
  Defender = task.defendKick(),
  Special = task.defendHead(),
  Assister = task.marking("First"),
  Breaker =task.marking("Second"),
  Crosser = task.marking("Third"),
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