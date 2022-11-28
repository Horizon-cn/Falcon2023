gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
    print("here zwc")
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.defendKick(),
  Assister = task.goMWPassPos("Leader"),
  Powerhouse = task.marking("Second"),
  Special = task.multiBack(3, 1), --sideBack(),
  Defender = task.marking("First"),
  Hawk = task.multiBack(3,2), --leftBack(),
  Middle = task.multiBack(3, 3), --rightBack(),
  Goalie = task.goalieNew(),
    match = "[L][APSD][HM]"
},
  name = "Ref_MiddleDefV11",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}