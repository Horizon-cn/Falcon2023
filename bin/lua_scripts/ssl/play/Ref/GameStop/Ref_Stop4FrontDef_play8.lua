gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  --MiddleAttack_8
  --三個在前
    Leader = task.defendKick(),
    Assister = task.goMWPassPos("Leader"),
    Special = task.markingFront("Second"),
    Middle = task.markingFront("First"),
    Defender = task.multiBack(3,1),
    Crosser  = task.multiBack(3,2),
    Breaker  = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[L][DCB][S][A][M]"
},
  name = "Ref_Stop4FrontDef_play8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}