gPlayTable.CreatePlay {

firstState = "start",

["start"] = {
  switch = function()
    if cond.isGameOn() then
        return "exit"
    end
  end,

  Assister = task.stop(),
  Special  = task.stop(),
  Leader   = task.stop(),
  -- Fronter  = task.stop(),
  -- Center   = task.stop(),
  Defender = task.stop(),
  Middle   = task.stop(),
  Goalie   = task.stop(),
  Goaile   = task.stop(),
  match    = "[AMDLS]"
},

name = "Ref_StopV2",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
