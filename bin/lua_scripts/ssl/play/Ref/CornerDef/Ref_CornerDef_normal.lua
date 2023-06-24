gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
    Leader   = task.defendMiddle(),
    Assister = task.defendHead(),
    Special  = task.markingFront("First"),
    Breaker  = task.markingFront("Second"),
    Crosser  = task.multiBack(3,1),
    Middle   = task.multiBack(3,2),
    Defender = task.multiBack(3,3),
    Goalie   = task.goalieNew(),
    match    = "[CM][A][S][L][BD]"
},
  name = "Ref_CornerDef_normal",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}