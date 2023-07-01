
gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Leader") < 20 , 30, 1000) then
        return "start"
      end
    end,
    Leader = task.advance(),
    Hawk = task.GoSupport("Leader",1),
    match    = "[L][H]"
  },


  name = "Ref_CornerKickV2",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
