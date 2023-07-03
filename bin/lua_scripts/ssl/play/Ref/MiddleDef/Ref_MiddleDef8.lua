gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.sideBack(),
  Hawk = task.multiBack(4,1),
  Middle = task.multiBack(4,2),
  Special = task.multiBack(4,3),
  Assister = task.markingFront("First"),
  Powerhouse = task.markingFront("Second"),
  Defender = task.multiBack(4,4),
  Goalie = task.goalieNew(),
  match    = "[HMSD][L][AP]"
},
  name = "Ref_MiddleDef8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}
