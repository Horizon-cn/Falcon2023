local TMP=CGeoPoint:new_local(250,-150)
local midpoint=CGeoPoint:new_local(-150,-250)

gPlayTable.CreatePlay {

  firstState = "get",

  ["get"] = {
    switch = function()
      if bufcnt(player.velMod("Tier")<10 and player.toBallDist("Kicker")<20,"fast") then
        return "pass1"
      end
    end,
    Kicker   = task.staticGetBall(midpoint),
    Receiver = task.goTechChalPos("Kick"),
    Tier     = task.goTechChalPos("Pass"),
    match    = ""
  },

  ["pass1"]= {
    switch = function()
      if player.isBallPassed("Kicker","Tier") then
        return "receive1"
      end
    end,
    Kicker   = task.pass("Tier"),
    Receiver = task.goTechChalPos("Kick"),
    Tier     = task.goTechChalPos("Pass"),
    match    = ""
  },

  ["receive1"]= {
    switch = function()
      if bufcnt(player.toBallDist("Tier")<20,"normal") then
        return "pass2"
      end
    end,
    Kicker   = task.stop(),
    Receiver = task.goTechChalPos("Kick"),
    Tier     = task.receive("Kicker"),
    match    = ""
  },

  ["pass2"]= {
    switch = function()
      -- if player.isBallPassed("Tier","Receiver") then
        if player.kickBall("Tier") then
        return "receive2"
      end
    end,
    Kicker   = task.stop(),
    Receiver = task.goTechChalPos("Kick"),
    Tier     = task.pass("Receiver"),
    match    = ""
  },

  ["receive2"]= {
    switch = function()
      if bufcnt(player.toBallDist("Receiver")<20,"normal") then
        return "shoot"
      end
    end,
    Kicker   = task.stop(),
    Receiver = task.receive("Tier"),
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
    match=""
  },

  name = "Ref_BackKickV1",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}