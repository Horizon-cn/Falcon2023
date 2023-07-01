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
    Leader = task.markingFront("Second"),
    Assister = task.defendMiddle(), --改跑點
    Middle =  task.defendKick(), 
    Special = task.markingFront("First"),
    Defender = task.multiBack(3,1),
    Crosser  = task.multiBack(3,2),
    Breaker  = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[DC][M][L][A][B][S]"
},
  name = "Ref_FrontDef_normal",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}