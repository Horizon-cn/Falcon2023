gPlayTable.CreatePlay{

  firstState = "get",

  ["get"] = {
    switch = function()
      if bufcnt(player.velMod("Receiver")<10 and player.toBallDist("Kicker")<30,"fast") then
        return "pass"
      end
    end,
    Kicker   = task.staticGetBall("Receiver"),
    Receiver = task.goTechChalPos("Kick"),
    Tier     = task.stop(),
    match    = ""
  },

  ["pass"]= {
    switch = function()
      if player.isBallPassed("Kicker","Receiver") then
        return "receive"
      end
    end,
    Kicker   = task.pass("Receiver"),
    Receiver = task.goTechChalPos("Kick"),
    Tier     = task.stop(),
    match    = ""
  },

  ["receive"]= {
    switch = function()
      if bufcnt(player.toBallDist("Receiver")<20,"normal") then
        return "shoot"
      end
    end,
    Kicker   = task.stop(),
    Receiver = task.receive("Kicker"),
    Tier     = task.stop(),
    match    = ""
  },

  ["shoot"]= {
    switch = function()
      if player.kickBall("Receiver") then
        return "advance"
      end
    end,
    Kicker   = task.goSecondPassPos("Receiver"),
    Receiver = task.chaseNew(),
    Tier     = task.goFirstPassPos("Receiver"),
    match    = ""
  },

  ["advance"]= {
    switch = function()
      return "advance"
    end,
    Kicker   = task.goSecondPassPos("Receiver"),
    Receiver = task.advance(),
    Tier     = task.goFirstPassPos("Receiver"),
    match    = ""
  },

  name = "Ref_CornerKickV1",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
