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
  Special = task.goMWPassPos("Leader"),
  Assister = task.goCmuRush(CGeoPoint:new_local(-460/1200*param.pitchLength,0/900*param.pitchWidth)),
  Powerhouse = task.goCmuRush(CGeoPoint:new_local(-460/1200*param.pitchLength,140/900*param.pitchWidth)),
  Defender = task.multiBack(3,3),
  Goalie = task.goalieNew(),
  match    = "[L][HM][SAPD]"
},
  name = "Ref_MiddleDef8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}