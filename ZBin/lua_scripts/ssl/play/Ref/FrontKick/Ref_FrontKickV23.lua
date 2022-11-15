-- -- 2012年进SKUBA战术的加强版，前面跑位一模一样，后面的冲刺换成后卫前冲
-- -- by zhyaic 2013.6.16
-- -- 2014-07-20 yys 改

-- --2020-11-07 改成forntKick
-- local chipPower = 200
-- -- local TARGET_SHOOT_POS = CGeoPoint:new_local(450,-35)
-- -- local FINAL_SHOOT_POS = CGeoPoint:new_local(200,100)
-- -- local MIDDEL_FAKE_POS = ball.refAntiYPos(CGeoPoint:new_local(100,200))
-- local TMP_POS   = ball.refAntiYPos(CGeoPoint:new_local(0,0))
-- -- local SYNT_POS  = ball.refSyntYPos(CGeoPoint:new_local(220,50))
-- -- local SYNT_POS2  = {
-- --   ball.refSyntYPos(CGeoPoint:new_local(150,130)),
-- --   ball.refSyntYPos(CGeoPoint:new_local(200,150)),
-- -- }
-- -- local ANTIPOS_1 = ball.refAntiYPos(CGeoPoint:new_local(120,120))
-- -- local ANTIPOS_2 = ball.refAntiYPos(CGeoPoint:new_local(200,120))
-- -- local ANTIPOS_3 = ball.refAntiYPos(FINAL_SHOOT_POS)
-- --local KICK_POS  = pos.passForTouch(FINAL_SHOOT_POS)


-- local LEADER_READY_POS = ball.refAntiYPos(CGeoPoint:new_local(150,100))
-- local LEADER_KICK_POS = CGeoPoint:new_local(160,-90)
-- local PASS_POS = pos.passForTouch(LEADER_KICK_POS)

-- local SSS = ball.refSyntYPos(LEADER_KICK_POS)

-- -- local LEADER_KICK_POS = function ()
-- --   if ball.posY() > 0 then
-- --    return pos.passForTouch(CGeoPoint:new_local(160,-90))
-- --  else
-- --    return pos.passForTouch(CGeoPoint:new_local(160,90))
-- --   end
-- -- end

-- -- local ANTI_FAKE_POS = ball.refAntiYPos(CGeoPoint:new_local(380,200))
-- -- local ANTI_FAKE_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(380,-200))
-- -- local DIR_POS =ball.refAntiYPos(CGeoPoint:new_local(450,300))

-- gPlayTable.CreatePlay{

-- firstState = "start",

-- ["start"] = {
--   switch = function ()
--     if bufcnt( player.toTargetDist("Leader") < 20,  20 , 90 ) then
--       return "gopass"
--     end
--   end,
--   Assister = task.staticGetBall(PASS_POS),
--   Special  = task.defendMiddle(),
--   Leader   = task.goCmuRush(LEADER_READY_POS),
--   Middle   = task.leftBack(),
--   Defender = task.rightBack(),
--   Goalie   = task.goalie(),
--   match    = "{ADLSM}"
-- },

-- ["gopass"] = {
--   switch = function ()
--     if bufcnt(ball.toPlayerDist("Assister") > 30 or ball.velMod() > 150,"normal",90) then
--       return "exit"
--     end
--   end,
--   Assister = task.chipPass(PASS_POS, chipPower),
--   Special  = task.continue(),
--   Leader   = task.goCmuRush(SSS),
--   Middle   = task.leftBack(),
--   Defender = task.rightBack(),
--   Goalie   = task.goalie(),
--   match    = "{ADLSM}"
-- },

-- name = "Ref_FrontKickV23",
-- applicable ={
--   exp = "a",
--   a = true
-- },
-- score = 0,
-- attribute = "attack",
-- timeout = 99999
-- }

-- -- ["goshoot"] = {
-- --   switch = function ()
-- --     if bufcnt(player.toTargetDist("Special") < 60 and
-- --        player.toTargetDist("Leader") < 60,  "normal", 90) then
-- --       return "gopass"
-- --     end
-- --   end,
-- --   Assister = task.staticGetBall(KICK_POS),
-- --   Special  = task.goCmuRush(TMP_POS),
-- --   Leader   =task.goCmuRush(LEADER_READY_POS),
-- --   Middle   = task.leftBack(),
-- --   Defender = task.rightBack(),
-- --   Goalie   = task.goalie(),
-- --   match    = "{A}{DLSM}"
-- -- }
-- -- ["goalone"] = {
-- --   switch = function ()
-- --     if bufcnt(player.toTargetDist("Defender") < 60, "fast", 90) then
-- --       return "goget"
-- --     end
-- --   end,
-- --   Assister = task.slowGetBall(KICK_POS),
-- --   Special  = task.goCmuRush(SYNT_POS),
-- --   Leader   = task.leftBack(),
-- --   Middle   = task.rightBack(),
-- --   Defender = task.goCmuRush(ANTIPOS_1),
-- --   Goalie   = task.goalie(),
-- --   match    = "{DALSM}"
-- -- },

-- -- ["goget"] = {
-- --     switch = function ()
-- --     if bufcnt(player.toTargetDist("Defender") < 40, "fast", 90) then
-- --       return "gopass"
-- --     end
-- --   end,
-- --   Assister = task.slowGetBall(KICK_POS),
-- --   Special  = task.goCmuRush(SYNT_POS),
-- --   Leader   = task.singleBack(),
-- --   Middle   = task.defendMiddle(),  
-- --   Defender = task.goCmuRush(ANTIPOS_2),
-- --   Goalie   = task.goalie(),
-- --   match    = "{DALSM}"
-- -- },

-- -- ["gopass"] = {
-- --     switch = function ()
-- --     if bufcnt(player.kickBall("Assister") or
-- --           player.toBallDist("Assister") > 30,"fast", 90) then
-- --       return "goopen"
-- --     elseif  bufcnt(true, 120) then
-- --       return "exit"
-- --     end
-- --   end,
-- --   Assister = task.chipPass(KICK_POS, chipPower),
-- --   Special  = task.goCmuRush(SYNT_POS),
-- --   Leader   = task.singleBack(),
-- --   Middle   = task.defendMiddle(),
-- --   Defender = task.goCmuRush(ANTIPOS_3),
-- --   Goalie   = task.goalie(),
-- --   match    = "{DALSM}"
-- -- },

-- -- ["goopen"] = {
-- --     switch = function ()
-- --     if bufcnt(player.toTargetDist("Defender") < 35, "fast", 180) then
-- --       return "goreceive"
-- --     end
-- --   end,
-- --   Assister = task.goCmuRush(ANTI_FAKE_POS_2),
-- --   Special  = task.sideBack(),
-- --   Leader   = task.singleBack(),
-- --   Middle   = task.defendMiddle(),
-- --   Defender = task.goCmuRush(ball.refAntiYPos(FINAL_SHOOT_POS),player.toBallDir),
-- --   Goalie   = task.goalie(),
-- --   match    = "{DALSM}"
-- -- },

-- -- ["goreceive"] = {
-- --     switch = function ()
-- --     if player.kickBall("Defender") then
-- --       return "finish"
-- --     elseif bufcnt(player.toBallDist("Defender")<30, 3,120) then
-- --       return "gokick"
-- --     end
-- --   end,
-- --   Assister = task.defendMiddle("Defender"),
-- --   Special  = task.leftBack(),
-- --   Leader   = task.rightBack(),
-- --   Middle   = task.goCmuRush(ANTI_FAKE_POS),
-- --   Defender = task.goCmuRush(ball.refAntiYPos(FINAL_SHOOT_POS),player.toBallDir),
-- --   Goalie   = task.goalie(),
-- --   match    = "{DM}(ALS)"
-- -- },

-- -- ["gokick"] = {
-- --     switch = function ()
-- --     if bufcnt(player.kickBall("Defender"),1,60)then
-- --       return "finish"
-- --     end
-- --   end,
-- --   Assister = task.defendMiddle("Defender"),
-- --   Defender = task.advance(),
-- --   Middle   = task.goCmuRush(ANTI_FAKE_POS),
-- --   Special  = task.leftBack(),
-- --   Leader   = task.rightBack(),
-- --   Goalie   = task.goalie(),
-- --   match    = "{DM}(ALS)"


--CYM/FH 20221104


local chipPower = 250 --可用距离算
local ASIS_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(375,70))
local ASIS_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(385,110))
local ASIS_POS_3 = ball.refAntiYPos(CGeoPoint:new_local(145,-110))
local ASIS_POS_4 = ball.refAntiYPos(CGeoPoint:new_local(145,130))

local SHOOT_ASIS_POS = ball.refAntiYPos(CGeoPoint:new_local(350,-100))


local FAKE_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(270,-50))
local FAKE_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(450,210))
local FAKE_POS_11 = ball.refAntiYPos(CGeoPoint:new_local(260,-45))
local FAKE_POS_22 = ball.refAntiYPos(CGeoPoint:new_local(440,220))
--local SYNT_POS_3 = ball.refSyntYPos(CGeoPoint:new_local(300,180))


local SHOOT_POS = pos.passForTouch(ball.refAntiYPos(CGeoPoint:new_local(310,110)))
local Pre_SHOOT_POS = ball.refAntiYPos(CGeoPoint:new_local(310,110))
local dangerous = true

if ball.refPosY() > -140 and ball.refPosY() < 140 then
    chipPower=150
  else
    chipPower=250
end

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function ()
      if bufcnt(player.toTargetDist("Leader") < 20 , 6, 180) then
        return "pass"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS()),
    Leader   = task.goCmuRush(Pre_SHOOT_POS),
    Special  = task.goCmuRush(FAKE_POS_2),
    Middle   = task.goCmuRush(FAKE_POS_1),
    Defender = task.leftBack(),
    Goalie   = dangerous and task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{A}{DLSMH}{E}"
  },

 -- ["change"] = {
 --    switch = function ()
 --      if bufcnt(player.toTargetDist("Leader") < 20 , 30, 180) then
 --        return "pass"
 --      end
 --    end,
 --    Assister = task.staticGetBall(SHOOT_POS()),
 --    -- Leader   = task.goCmuRush(ASIS_POS_3),
 --    -- Special  = task.goCmuRush(ASIS_POS_2),
 --    -- Middle   = task.goCmuRush(ASIS_POS_1),
 --    Leader   = task.goCmuRush(SHOOT_POS),
 --    Special  = task.goCmuRush(FAKE_POS_2),
 --    Middle   = task.goCmuRush(FAKE_POS_1),
 --    Defender = task.leftBack(),
 --    Goalie   = task.goalie(),
 --    Engine   = task.singleBack(),
 --    Hawk     = task.rightBack(),
 --    match    = "{A}{DLSMH}{E}"
 --  }, 

  

  ["pass"] = {
    switch = function ()
      if player.kickBall("Assister") or player.toBallDist("Assister") > 30 then
        print("wait")
        return "waitBall"
      else
        print("exit")
      end
    end,
    Assister = task.chipPass(SHOOT_POS(),chipPower),
    Leader   = task.goCmuRush(Pre_SHOOT_POS,player.toPlayerDir("Assister")),
    Special  = task.goCmuRush(FAKE_POS_22),
    Middle   = task.goCmuRush(FAKE_POS_11),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{ADLSMEH}"
  },


  ["waitBall"] = {
    switch = function ()
      print("waitBall")
      if bufcnt(player.toPointDist("Leader", SHOOT_POS) < 10, 3, 60) then
        return "shoot"
      end
    end,
    Assister = task.goCmuRush(SHOOT_ASIS_POS),
    Leader   = task.goCmuRush(Pre_SHOOT_POS,player.toPlayerDir("Assister")),
    Special  = task.continue(),
    Middle   = task.continue(),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{ADL}{EH}{SM}"
  },

  ["shoot"] = {
    switch = function ()
      print("shoot")
      if bufcnt(player.kickBall("Leader"), "fast", 120) then
        print("exit")
        return "exit"
      end
    end,
    Assister = task.goCmuRush(ASIS_POS_4),
    Leader   = task.shootV2(),
    Special  = task.continue(),
    Middle   = task.continue(),
    Defender = task.leftBack(),
    Goalie   = task.goalie(),
    Engine   = task.singleBack(),
    Hawk     = task.rightBack(),
    match    = "{ADL}{EH}{SM}"
  },

  name = "Ref_FrontKickV23",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
