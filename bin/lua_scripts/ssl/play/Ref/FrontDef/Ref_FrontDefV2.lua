
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
  Assister = task.support("Assister",0),
  Goalie = task.goalieNew(),
  match    = "[L][DM][AS]"
},
  name = "Ref_FrontDefV2",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}