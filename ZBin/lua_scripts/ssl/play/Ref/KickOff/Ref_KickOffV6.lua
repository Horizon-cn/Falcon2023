--[[-- 直接传球
-- 在改一下V1

local CHIP_POS = CGeoPoint:new_local(200, 200)

local ASSISTER_POS_1 = CGeoPoint:new_local(-15, 230)
local ASSISTER_POS_2 = CGeoPoint:new_local(-60, 60)

local SPECIAL_POS_1  = CGeoPoint:new_local(-15, -230)
local SPECIAL_POS_2  = CGeoPoint:new_local(200, -60)

local MIDDLE_POS_1   = CGeoPoint:new_local(-220, 250)
local MIDDLE_POS_2   = CGeoPoint:new_local(-5, 250)


gPlayTable.CreatePlay{
firstState = "start",

["start"] = {
  switch = function ()
    if cond.isNormalStart() then
      return "temp"
    end
  end,
  Leader   = task.staticGetBall(CHIP_POS),
  Assister = task.goCmuRush(ASSISTER_POS_1),
  Special  = task.goCmuRush(SPECIAL_POS_1),
  Middle   = task.goCmuRush(MIDDLE_POS_1),
  Defender = task.singleBack(),
  Goalie   = task.goalieNew(),
  match    = "{LASMD}"
},

["temp"] = {
  switch = function ()
    if bufcnt(player.toPointDist("Assister", ASSISTER_POS_1) < 10 and player.toPointDist("Special", SPECIAL_POS_1) < 10, 60,100) then
      return "chip"
    end
  end,
  Leader   = task.staticGetBall(CHIP_POS),
  Assister = task.goCmuRush(ASSISTER_POS_1),
  Special  = task.goCmuRush(SPECIAL_POS_1),
  Middle   = task.goSpeciPos(MIDDLE_POS_1),
  Defender = task.singleBack(),
  Goalie   = task.goalieNew(),
  match    = "{LASMD}"
},


["chip"] = {
    switch = function ()
    --if bufcnt(player.kickBall("Leader"), "fast", 200) then
      if bufcnt(player.kickBall("Leader"), "fast", 200) then
      return "receive"
    end
  end,
  Leader   = task.goAndTurnKick("Assister", 500),
  Special  = task.goCmuRush(SPECIAL_POS_1),
  Middle   = task.defendMiddle(),
  Defender = task.rightBack(),
  Assister = task.goCmuRush(ASSISTER_POS_1),
  Goalie   = task.goalieNew(),
  match    = "{LASMD}"
},

["receive"] = {
  switch = function ()
    if bufcnt(player.toBallDist("Assister") < 20, "fast", 150) then
      return "exit"
    end
  end,
  Leader   = task.goCmuRush(CGeoPoint:new_local(200,20)),
  Special  = task.goCmuRush(SPECIAL_POS_2),
  Middle   = task.defendMiddle(),
  Defender = task.rightBack(),
  Assister = task.receiveShoot(),
  Goalie   = task.goalieNew(),
  match    = "{LASMD}"
},



name = "Ref_KickOffV6",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
--]]
local CHIP_POS = CGeoPoint:new_local(240, 200)

local ASSISTER_POS_1 = CGeoPoint:new_local(-20, 350)
local ASSISTER_POS_2 = CGeoPoint:new_local(-80, 90)

local SPECIAL_POS_1  = CGeoPoint:new_local(-20, -350)
local SPECIAL_POS_2  = CGeoPoint:new_local(280, -80)

local MIDDLE_POS_1   = CGeoPoint:new_local(-280, 375)
local MIDDLE_POS_2   = CGeoPoint:new_local(-10, 375)

local ENGINE_POS_1   = CGeoPoint:new_local(-280, -375)
local ENGINE_POS_2   = CGeoPoint:new_local(-60, -375)

local HAWK_POS_1   = CGeoPoint:new_local(-400, 0)
local HAWK_POS_2   = CGeoPoint:new_local(-450, 0)

gPlayTable.CreatePlay{
firstState = "start",

["start"] = {
  switch = function ()
    if cond.isNormalStart() then
      return "temp"
    end
  end,
  Leader   = task.staticGetBall(CHIP_POS),
  Assister = task.goCmuRush(ASSISTER_POS_1),
  Special  = task.goCmuRush(SPECIAL_POS_1),
  Middle   = task.goCmuRush(MIDDLE_POS_1),
  Defender = task.singleBack(),
  Goalie   = task.goalieNew(),
  Engine   = task.goCmuRush(ENGINE_POS_1),
  Hawk     = task.goCmuRush(HAWK_POS_1),
  match    = "{LASMDEH}"
},

["temp"] = {
  switch = function ()
    if bufcnt(player.toPointDist("Assister", ASSISTER_POS_1) < 10 and player.toPointDist("Special", SPECIAL_POS_1) < 10, 60,100) then
      return "chip"
    end
  end,
  Leader   = task.staticGetBall(CHIP_POS),
  Assister = task.goCmuRush(ASSISTER_POS_1),
  Special  = task.goCmuRush(SPECIAL_POS_1),
  Middle   = task.goSpeciPos(MIDDLE_POS_1),
  Defender = task.singleBack(),
  Goalie   = task.goalieNew(),
  Engine   = task.goCmuRush(ENGINE_POS_1),
  Hawk     = task.goCmuRush(HAWK_POS_1),
  match    = "{LASMDEH}"
},


["chip"] = {
    switch = function ()
    --if bufcnt(player.kickBall("Leader"), "fast", 200) then
      if bufcnt(player.kickBall("Leader"), "fast", 200) then
      return "receive"
    end
  end,
  Leader   = task.chipPass(CHIP_POS), --goAndTurnKick("Assister", 500),
  Special  = task.goCmuRush(SPECIAL_POS_1),
  Middle   = task.defendMiddle(),
  Defender = task.rightBack(),
  Assister = task.goCmuRush(ASSISTER_POS_1),
  Goalie   = task.goalieNew(),
  Engine   = task.singleBack(),
  Hawk     = task.goCmuRush(HAWK_POS_2),
  match    = "{LASMDEH}"
},

["receive"] = {
  switch = function ()
    if bufcnt(player.toBallDist("Assister") < 20, "fast", 150) then
      return "exit"
    end
  end,
  Leader   = task.goCmuRush(CGeoPoint:new_local(200,20)),
  Special  = task.goCmuRush(SPECIAL_POS_2),
  Middle   = task.defendMiddle(),
  Defender = task.rightBack(),
  Assister = task.receiveShoot(),
  Goalie   = task.goalieNew(),
  Engine   = task.singleBack(),
  Hawk     = task.leftBack(),
  match    = "{LASMDEH}"
},



name = "Ref_KickOffV6",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
