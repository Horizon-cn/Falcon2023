gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
    --MiddleDefendBalance_8
    --三個在前
    Leader = task.defendKick(),
    Assister = task.support("Leader",0),
    Middle = task.markingFront("Second"),
    Special = task.markingFront("First"),
    Defender = task.multiBack(3,1),
    Crosser  = task.multiBack(3,2), 
    Breaker  = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[L][DCB][M][SA]"
},
  name = "Ref_Stop4MiddleDef_play8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}