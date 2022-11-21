local READY_POS1 = ball.refSyntYPos(CGeoPoint:new_local(-460,120))
local READY_POS2 = CGeoPoint:new_local(-460,0)
local READY_POS3 = ball.refAntiYPos(CGeoPoint:new_local(-460,120))

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
    switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
    Kicker   = task.goCmuRush(READY_POS1),
    Receiver = task.goCmuRush(READY_POS2),
    Tier     = task.goCmuRush(READY_POS3),
    match    = ""
  },

  name = "Ref_Stop4ChaKick",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "attack",
  timeout = 99999
}