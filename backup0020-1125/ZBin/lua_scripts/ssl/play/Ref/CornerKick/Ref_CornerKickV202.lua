--针对对方少车的情况写的角球脚本 by Fantasy

--[[ 关键常量宏定义 ]]
local halfPitchX = param.pitchLength/2    -- 半场长度
local halfPitchY = param.pitchWidth/2   -- 半场宽度
local halfGoalW = param.goalWidth/2

local CHIP_POWER = 200--237

local SHOOT_TARGET_POS = function ()
  -- 函数功能:计算出射门死角位置
  return function ()
    return CGeoPoint:new_local(halfPitchX,-ball.refAntiY()*(halfGoalW-20))
  end
end

local SHOOT_TARGET = SHOOT_TARGET_POS()



local REAL_SHOOT_POS = CGeoPoint:new_local(320, 30)
local FAKE_SHOOT_POS = CGeoPoint:new_local(300, 70)

local PASS_POS   = pos.passForTouch(REAL_SHOOT_POS)




--[1]
local DEFENDER_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(100, 80))
local LEADER_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(310, -170))   --FAKER
local LEADER_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(370, -130)) 
local MIDDLE_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(100, -100))  
local SPEFCIAL_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(235, -100)) 




--[2]
local MIDDLE_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(240, -100)) 
local MIDDLE_POS_3 = ball.refAntiYPos(CGeoPoint:new_local(280, -100)) 


local TMP_DEFENDER_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(290, 50)),
 -- ball.refAntiYPos(CGeoPoint:new_local(330, 160)),
  ball.refAntiYPos(REAL_SHOOT_POS)
}

local DEFEND_POS_0 = ball.refAntiYPos(REAL_SHOOT_POS)
local TMP_LEADER_POS= {
  ball.refAntiYPos(CGeoPoint:new_local(165, -5)),
  --ball.refAntiYPos(CGeoPoint:new_local(300, 50)),
  ball.refAntiYPos(FAKE_SHOOT_POS)
}

local TMP_SPECIAL_POS= {
  ball.refAntiYPos(CGeoPoint:new_local(300, -180)),
  ball.refAntiYPos(CGeoPoint:new_local(325, -125))
}



local GOALIE_MULTI_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(-80, 140)),
  ball.refAntiYPos(CGeoPoint:new_local(60, 140))
}

local dangerous = true
local USE_CHIP  = true

gPlayTable.CreatePlay{
  firstState = "start",
  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Defender") < 30 , 10 , 120) then
                --player.toTargetDist("Defender") < 30 and
                --player.toTargetDist("Special") < 30, 10, 150) then
        return "runTmpPos"
      end
    end,
    Assister = task.staticGetBall(PASS_POS),
    Leader   = task.goCmuRush(LEADER_POS_1, _, 600, flag.allow_dss),
    Special  = task.rightBack(),
    Middle   = task.leftBack(), 
    Defender = task.goCmuRush(DEFENDER_POS_1, _, 600, flag.allow_dss),
    Goalie   = dangerous and task.goalieNew() or task.goCmuRush(ANTI_POS_1, _, 350),
    match    = "{A}{MD}{LS}"
  },

  ["runTmpPos"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Defender", TMP_LEADER_POS[1]) < 20 ,3,80)then
        return "passBall"
      end
    end,
    --Assister = USE_CHIP and task.slowGetBall(PASS_POS) or task.staticGetBall(PASS_POS),
    Assister = task.slowGetBall(PASS_POS),
    Leader   = task.goCmuRush(LEADER_POS_1),
    Special  = task.rightBack(),
    Middle   = task.leftBack(), 
    Defender = task.goCmuRush(TMP_DEFENDER_POS[1]),
    Goalie   = dangerous and task.goalieNew() or task.goCmuRush(ANTI_POS_1, _, 350),
    match    = "{AMDLS}"
  },

  ["passBall"] = {
    switch = function ()
       if bufcnt(player.kickBall("Assister") or player.toBallDist("Assister") > 30 , 10,60) then
        return "waitBall"
      end
    end,
    --Assister = USE_CHIP and task.chipPass(PASS_POS, CHIP_POWER) or task.goAndTurnKick(PASS_POS, 450),
    Assister = task.chipPass(PASS_POS,CHIP_POWER),
    Leader   = task.goCmuRush(LEADER_POS_2),
    Special  = task.rightBack(),
    Middle   = task.leftBack(), 
    Defender = task.goCmuRush(DEFEND_POS_0),
    Goalie   = task.goalieNew(),
    match    = "{AMLDS}"
  },

  ["waitBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Defender", TMP_DEFENDER_POS[2]) < 30, 3, 60) then
        return "shootBall"
      end
    end,
    Assister = task.defendMiddle(),
    Leader   = task.continue(),
    Special  = task.rightBack(),
    Middle   = task.leftBack(),
    Defender = task.continue(),
    Goalie   = task.goalieNew(),
    match    = "{AMDLS}"
  },

  ["shootBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Defender") or player.kickBall("Leader"), "fast", 120)  then
        return "exit"
      end
    end,
    Assister = task.defendMiddle(),
    --Leader   = task.goCmuRush(TMP_LEADER_POS[3], _, 600, flag.allow_dss),
    Leader   = task.continue(),
    Special  = task.rightBack(),
    Middle   = task.leftBack(),
    Defender = task.touch(SHOOT_TARGET),
    --Defender = task.goCmuRush(TMP_LEADER_POS[3], _, 600, flag.allow_dss)
    Goalie   = task.goalieNew(),
    match    = "{AMDLS}"
  },

  name = "Ref_CornerKickV202",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999
}

-- --针对对方少车的情况写的角球脚本 by Fantasy

-- --[[ 关键常量宏定义 ]]
-- local halfPitchX = param.pitchLength/2    -- 半场长度
-- local halfPitchY = param.pitchWidth/2   -- 半场宽度
-- local halfGoalW = param.goalWidth/2

-- local CHIP_POWER = 235

-- local SHOOT_TARGET_POS = function ()
--   -- 函数功能:计算出射门死角位置
--   return function ()
--     return CGeoPoint:new_local(halfPitchX,-ball.refAntiY()*(halfGoalW-20))
--   end
-- end

-- local SHOOT_TARGET = SHOOT_TARGET_POS()



-- local REAL_SHOOT_POS = CGeoPoint:new_local(375, 125)
-- local FAKE_SHOOT_POS = CGeoPoint:new_local(300, 70)
-- local PASS_POS   = pos.passForTouch(REAL_SHOOT_POS)




-- --[1]
-- local DEFENDER_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(100, 80))
-- local LEADER_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(165, -100))   --FAKER
-- local MIDDLE_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(100, -100))  
-- local SPEFCIAL_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(235, -100)) 




-- --[2]
-- local MIDDLE_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(240, -100)) 
-- local MIDDLE_POS_3 = ball.refAntiYPos(CGeoPoint:new_local(280, -100)) 


-- local TMP_DEFENDER_POS = {
--   ball.refAntiYPos(CGeoPoint:new_local(260, 170)),
--   ball.refAntiYPos(CGeoPoint:new_local(330, 160)),
--   ball.refAntiYPos(REAL_SHOOT_POS)
-- }

-- local TMP_LEADER_POS= {
--   ball.refAntiYPos(CGeoPoint:new_local(165, -5)),
--   ball.refAntiYPos(CGeoPoint:new_local(300, 50)),
--   ball.refAntiYPos(FAKE_SHOOT_POS)
-- }

-- local TMP_SPECIAL_POS= {
--   ball.refAntiYPos(CGeoPoint:new_local(300, -180)),
--   ball.refAntiYPos(CGeoPoint:new_local(325, -125))
-- }



-- local GOALIE_MULTI_POS = {
--   ball.refAntiYPos(CGeoPoint:new_local(-80, 140)),
--   ball.refAntiYPos(CGeoPoint:new_local(60, 140))
-- }

-- local dangerous = true
-- local USE_CHIP  = true

-- gPlayTable.CreatePlay{
--   firstState = "start",
--   ["start"] = {
--     switch = function ()
--       if bufcnt(player.toTargetDist("Leader") < 30 and
--                 player.toTargetDist("Defender") < 30 and
--                 player.toTargetDist("Special") < 30, 20, 150) then
--         return "runTmpPos"
--       end
--     end,
--     Assister = task.staticGetBall(PASS_POS),
--     Leader   = task.goCmuRush(LEADER_POS_1, _, 600, flag.allow_dss),
--     Special  = task.goCmuRush(SPEFCIAL_POS_1, _, 600, flag.allow_dss),
--     Middle   = task.goCmuRush(MIDDLE_POS_1, _, 600, flag.allow_dss),
--     Defender = task.goCmuRush(DEFENDER_POS_1, _, 600, flag.allow_dss),
--     Goalie   = dangerous and task.goalieNew() or task.goCmuRush(ANTI_POS_1, _, 350),
--     match    = "{A}{DL}{MS}"
--   },

--   ["runTmpPos"] = {
--     switch = function ()
--       if bufcnt(player.toPointDist("Defender", TMP_DEFENDER_POS[2]()) < 20 ,3,120)then
--         return "passBall"
--       end
--     end,
--     Assister = USE_CHIP and task.slowGetBall(PASS_POS) or task.staticGetBall(PASS_POS),
--     Leader   = task.runMultiPos(TMP_LEADER_POS, false, 40),
--     Special  = task.runMultiPos(TMP_SPECIAL_POS, false, 40),
--     Middle   = task.goCmuRush(MIDDLE_POS_2, _, 600, flag.allow_dss),
--     Defender = task.runMultiPos(TMP_DEFENDER_POS, false, 40),
--     Goalie   = dangerous and task.goalieNew() or task.goCmuRush(ANTI_POS_1, _, 350),
--     match    = "{ALDMS}"
--   },

--   ["passBall"] = {
--     switch = function ()
--        if bufcnt(player.kickBall("Assister") or player.toBallDist("Assister") > 30 , 30,60) then
--         return "waitBall"
--       end
--     end,
--     Assister = USE_CHIP and task.chipPass(PASS_POS, CHIP_POWER) or task.goAndTurnKick(PASS_POS, 450),
--     Leader   = task.continue(),
--     Special  = task.continue(),
--     Middle   = task.goCmuRush(MIDDLE_POS_3, _, 600, flag.allow_dss), 
--     Defender = task.continue(),
--     Goalie   = task.goalieNew(),
--     match    = "{ALDMS}"
--   },

--   ["waitBall"] = {
--     switch = function ()
--       if bufcnt(player.toPointDist("Defender", TMP_DEFENDER_POS[3]()) < 20, 3, 100) then
--         return "shootBall"
--       end
--     end,
--     Assister = task.stop(),
--     Leader   = task.continue(),
--     Special  = task.rightBack(),
--     Middle   = task.leftBack(),
--     Defender = task.continue(),
--     Goalie   = task.goalieNew(),
--     match    = "{ALDMS}"
--   },

--   ["shootBall"] = {
--     switch = function ()
--       if bufcnt(player.kickBall("Defender"), "fast", 120)  then
--         return "exit"
--       end
--     end,
--     Assister = task.goSupportPos("Defender"),
--     Leader   = task.goCmuRush(TMP_LEADER_POS[3], _, 600, flag.allow_dss),
--     Special  = task.rightBack(),
--     Middle   = task.leftBack(),
--     Defender = task.touch(SHOOT_TARGET),
--     Goalie   = task.goalieNew(),
--     match    = "{ALDMS}"
--   },

--   name = "Ref_CornerKickV30",
--   applicable = {
--     exp = "a",
--     a   = true
--   },
--   attribute = "attack",
--   timeout = 99999
-- }