
gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Leader") < 20 , 30, 180) then
        return "exit"
      end
    end,
    Leader = task.advance(),
    Hawk = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.goMWPassPos("Leader"),
    Assister = task.goCmuRush(CGeoPoint:new_local(-460, 0)),
    Powerhouse = task.goCmuRush(CGeoPoint:new_local(-460, 140)),
    Defender = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match    = "[L][HM][SAPD]"
  },


  name = "Ref_BackKickV2",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}