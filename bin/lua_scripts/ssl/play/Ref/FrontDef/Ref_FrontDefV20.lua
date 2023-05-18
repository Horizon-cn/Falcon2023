
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
  Special = task.marking("First"),
  Assister = task.marking("Second"),
  Goalie = task.goalieNew(),
  match    = "[L][MD][S][A]"
},
  name = "Ref_FrontDefV20",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}