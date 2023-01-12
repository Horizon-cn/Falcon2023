
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
  Powerhouse = task.marking("Second"),
  Special = task.multiBack(3, 1),
  Defender = task.marking("First"),
  Hawk = task.multiBack(3,2),
  Middle = task.multiBack(3, 3),
  Goalie = task.goalieNew(),
  match = "[L][SH][D][PMA]"
},
  name = "Ref_BackDefV12",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}