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
    Leader = task.markingFront("First"),
    Assister = task.markingFront("Third"),
    Middle = task.defendKick(),
    Special = task.markingFront("Second"),
    Defender = task.multiBack(3,1),
    Crosser  = task.multiBack(3,2), 
    Breaker  = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[DC][LS][B][M][A]"
},
  name = "Ref_MiddleDef_normal",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}