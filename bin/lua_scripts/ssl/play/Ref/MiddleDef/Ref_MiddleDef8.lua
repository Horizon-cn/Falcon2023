gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.sideBack(),
  Hawk = task.multiBack(3,1),
  Middle = task.multiBack(3,2),
  Special = task.multiBack(3,3),
  Assister = task.markingFront("First"),
  Powerhouse = task.markingFront("Second"),
  Defender = task.defendKick(),
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
