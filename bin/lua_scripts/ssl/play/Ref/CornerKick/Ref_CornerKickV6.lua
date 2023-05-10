--[[
  脚本作者: 陈锴锋(2020.02.21)
  核心战术: 前锋中卫后卫完美吸引防守到发球对角侧角区，守门员前插至同侧前场，
  发球车挑球给守门员，守门员单挑对方守门员死角射门
  注: 该脚本针对角球防守脚本Ref_CornerDefV4和V5，一传一射位置及力度有待改善
--]]

-- 11.10注: 该脚本针对全marking有奇效

--[[ 关键常量宏定义 ]]
local halfPitchX = param.pitchLength/2    -- 半场长度
local halfPitchY = param.pitchWidth/2   -- 半场宽度
local halfGoalW = param.goalWidth/2
local timeDelay = 120
local chipPower = 280
local flatPower = 566
--[[ 战术标志位宏定义 ]]
local USE_CHIP = true     -- 是否挑球，对角球防守脚本V4挑球和平传皆可
              -- 针对防守脚本V5此项需设成true
local USE_CHEAT = false  -- 是否欺骗防守，即Assister拿球时朝向角区
              -- 误导defendKick()位置，实际效果不理想

--[[ 各角色跑动点位定义 ]]
local CHEAT_POS = ball.refAntiYPos(CGeoPoint:new_local(350,0))  -- USE_CHEAT为真时，Assister拿球朝向位置

-- local SHOOT_POS_CNT = function()
--  -- 该函数计算出Goalie射门点、Assister挑球点以及射门目标位置
--  -- 微调参数可以提高一传一射成功率以及射门死角准确率
--  local tmpX,tmpY
--  local chip_pos, shoot_pos, target_pos
--  tmpX = 0.3 * halfPitchX
--  tmpY = 0.15 * halfPitchY
--  shoot_pos = ball.refSyntYPos(CGeoPoint:new_local(tmpX,tmpY))
--  if ball.posY()>0 then 
--    chip_pos = CGeoPoint:new_local(tmpX+2,tmpY-5)
--    target_pos = CGeoPoint:new_local(halfPitchX,halfGoalW-10)
--  else
--    chip_pos = CGeoPoint:new_local(tmpX+2,-tmpY+5)
--    target_pos = CGeoPoint:new_local(halfPitchX,-halfGoalW+10)
--  end
--  return shoot_pos, chip_pos, target_pos
-- end

local TARGET_POS_CNT = function ()
  -- 函数功能:计算出射门死角位置
  return function ()
    return CGeoPoint:new_local(halfPitchX,-ball.refAntiY()*(halfGoalW-10))
  end
end
-- 射门位置
local FINAL_SHOOT_POS = ball.refSyntYPos(CGeoPoint:new_local(0.25*halfPitchX,0.9*halfPitchY))
-- 传球位置
local CHIP_POS = CGeoPoint:new_local(0.25 * halfPitchX,-(0.3*halfPitchY))
-- 射门方向
local TARGET_POS = TARGET_POS_CNT()

-- local FINAL_SHOOT_POS, CHIP_POS, TARGET_POS = SHOOT_POS_CNT()

-- 存放每辆车的跑点位置，使用runMultiPos函数调用连续跑点
local SPECIAL_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(0.75*halfPitchX,0.75*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.8*halfPitchX,0.95*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.9*halfPitchX,0.95*halfPitchY)),
}
local LEADER_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(0.65*halfPitchX,0.65*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.6*halfPitchX,0.95*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.9*halfPitchX,0.95*halfPitchY)),
}
local MIDDLE_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(0.55*halfPitchX,0.55*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.4*halfPitchX,0.95*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.8*halfPitchX,0.95*halfPitchY)),
}
local DEFENDER_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(0.45*halfPitchX,0.45*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.2*halfPitchX,0.95*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.7*halfPitchX,0.95*halfPitchY)),
}
local GOALIE_POS = {
  ball.refSyntYPos(CGeoPoint:new_local(-0.7*halfPitchX,0.3*halfPitchY)),
  ball.refSyntYPos(CGeoPoint:new_local(-0.3*halfPitchX,0.3*halfPitchY)),
  ball.refSyntYPos(CGeoPoint:new_local(0.1*halfPitchX,0.3*halfPitchY)),
  FINAL_SHOOT_POS,
}


gPlayTable.CreatePlay{

firstState = "beginning",

["beginning"] = {     -- 起始动作: Assister拿球，守门员出动
  switch = function()
    if bufcnt(player.toTargetDist("Defender") < 20
          and player.toTargetDist("Assister") < 20, fast, 100) then
      return "attraction"
    end
  end,
    Assister = USE_CHEAT and task.staticGetBall(CHEAT_POS) or task.staticGetBall(CHIP_POS),
    Special  = task.goCmuRush(SPECIAL_POS[1]),    -- 
    Leader   = task.goCmuRush(LEADER_POS[1]),   --  此处均可用runMultiPos函数替代，减少状态机数量
    Middle   = task.goCmuRush(MIDDLE_POS[1]),   --
    Defender = task.goCmuRush(DEFENDER_POS[1]),   --
    Goalie   = task.runMultiPos(GOALIE_POS, false, 30, _, 600),
    match    = "{A}{DLSM}"
},

["attraction"] = {      -- 吸引防守: 前锋中卫后卫将对方盯防四车及牛角位盯防吸引至对角侧角区
  switch = function()
  local tmpDist = USE_CHEAT and 240 or 60
    if bufcnt(player.toPointDist("Goalie",GOALIE_POS[4]) < tmpDist, fast, 100) then
      return "passBall"
    end
  end,  --USE_CHEAT and task.staticGetBall(CHEAT_POS, false) or task.staticGetBall(CHIP_POS),
  Assister = USE_CHEAT and task.staticGetBall(CHEAT_POS) or task.staticGetBall(CHIP_POS),
    Special  = task.goCmuRush(SPECIAL_POS[2]),
    Leader   = task.goCmuRush(LEADER_POS[2]),
    Middle   = task.goCmuRush(MIDDLE_POS[2]),
    Defender = task.goCmuRush(DEFENDER_POS[2]),
    Goalie   = task.continue(),
    match    = "{A}{DLSM}"
},

["passBall"] = {      -- 开球传中: 守门员就位后，Assister传中，同时中卫后卫回防防止反杀
  switch = function()
    if bufcnt(player.kickBall("Assister"), fast, timeDelay) then
      return "shot"
    end
  end,
  Assister = USE_CHEAT and task.goAndTurnChip(CHIP_POS, chipPower) or task.chipPass(CHIP_POS, chipPower),
    Special  = task.goCmuRush(SPECIAL_POS[3]),
    Leader   = task.goCmuRush(LEADER_POS[3]),
    Middle   = task.leftBack(),
    Defender = task.rightBack(),
    Goalie   = task.goCmuRush(FINAL_SHOOT_POS, dir.compensate(TARGET_POS), 300),
    match    = "{A}{DLSM}"
},

["shot"] = {        -- 守门员射球门死角，前锋防止翻车advance补射
  switch = function()
    if bufcnt(player.kickBall("Goalie"),
        10, time) then
      return "exit"
    end
  end,
  Assister = task.goSupportPos("Goalie"),
    Special  = task.advance(),
    Leader   = task.advance(),
    Middle   = task.leftBack(),
    Defender = task.rightBack(),
    Goalie   = task.touch(TARGET_POS),
    match    = "{A}{DLSM}"
},

name = "Ref_CornerKickV6",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}