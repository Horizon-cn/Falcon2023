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
local LEFT_POS = CGeoPoint:new_local(200, -165)
local LEFT_POS_2 = CGeoPoint:new_local(300, -165)

local START_POS = CGeoPoint:new_local(35, 0)
local START_POS_1 = CGeoPoint:new_local(20, 0)
local RECEIVE_POS = CGeoPoint:new_local(-110, -70)

local RIGHT_POS_1  = CGeoPoint:new_local(-20, 80)
local RIGHT_POS_2  = CGeoPoint:new_local(155, 80)
local outside = CGeoPoint:new_local(-50,300)


gPlayTable.CreatePlay{
firstState = "start",

["start"] = {
  switch = function ()
    if cond.isNormalStart() then
      return "temp"
    end
  end,
  Leader   = task.goCmuRush(START_POS,-3,_,flag.allow_dss),
  Assister = task.multiBack(4,1);
  Special  = task.multiBack(4,2);
  Middle   = task.multiBack(4,3);
  Defender = task.multiBack(4,4);
  Goalie   = task.goalieNew(),
  match    = "[L][ASMD]"
},

["temp"] = {
  switch = function ()
    if bufcnt(player.toTargetDist("Leader")<20 ,50,100) then
      return "kickof"
    end
  end,
  Leader   = task.goCmuRush(START_POS_1,-3,_,flag.allow_dss),  --staticGetBall(player.toPlayerDir("Assister","Leader")),
  Assister = task.multiBack(4,1);
  Special  = task.multiBack(4,2);
  Middle   = task.multiBack(4,3);
  Defender = task.multiBack(4,4);
  Goalie   = task.goalieNew(),
  match    = "[L][ASMD]"
},


["kickof"] = {
    switch = function ()
    --if bufcnt(player.kickBall("Leader"), "fast", 200) then
      if bufcnt(player.toBallDist("Leader") > 30) then
      return "exit"
    end
  end,
  Leader   = task.passToPos(outside,300)
  Assister = task.multiBack(4,1);
  Special  = task.multiBack(4,2);
  Middle   = task.multiBack(4,3);
  Defender = task.multiBack(4,4);
  Goalie   = task.goalieNew(),
  match    = "[L][ASMD]"
},



name = "Ref_KickOffV230",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
