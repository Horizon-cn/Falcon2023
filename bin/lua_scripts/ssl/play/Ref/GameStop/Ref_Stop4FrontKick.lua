-- 前场球定位球在stop阶段进行站位
-- FanHao 2022-10-26
local halfPitchX = param.pitchLength/2    -- 半场长度
local halfPitchY = param.pitchWidth/2   -- 半场宽度
local halfGoalW = param.goalWidth/2

local STOP_FLAG  = bit:_or(flag.slowly, flag.dodge_ball)
local STOP_DSS   = bit:_or(STOP_FLAG, flag.allow_dss)
local KICK_POS   = function ()
	return ball.syntYPos(CGeoPoint:new_local(ball.posX() - 59, param.pitchWidth/2-18))()
end

local SHOOT_DIR  = ball.antiYDir(1.57)

local READY_POS_1 = ball.refAntiYPos(CGeoPoint:new_local(100,250))
local READY_POS_2 = ball.refAntiYPos(CGeoPoint:new_local(150,-250))
local FRONT_POS = ball.refAntiYPos(CGeoPoint:new_local(300,100))

local READY_POS = ball.refAntiYPos(CGeoPoint:new_local(250,-90))

local PENALTY_POS = ball.refAntiYPos(CGeoPoint:new_local(-60,0))

local ACC = 300

local SPECIAL_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(270,240)),
  ball.refAntiYPos(CGeoPoint:new_local(0.75*halfPitchX,0.75*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.8*halfPitchX,0.95*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.9*halfPitchX,0.95*halfPitchY)),
}
local LEADER_POS = {
ball.refAntiYPos(CGeoPoint:new_local(-85,-50)),
ball.refAntiYPos(CGeoPoint:new_local(-100,0)),
ball.refAntiYPos(CGeoPoint:new_local(-85,50)),
ball.refAntiYPos(CGeoPoint:new_local(-85,0)),
}
local MIDDLE_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(270,215)),
  ball.refAntiYPos(CGeoPoint:new_local(340,215)),
  ball.refAntiYPos(CGeoPoint:new_local(335,115)),
  ball.refAntiYPos(CGeoPoint:new_local(380,220)),

}
local DEFENDER_POS = {
  ball.refAntiYPos(CGeoPoint:new_local(0.45*halfPitchX,0.45*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.2*halfPitchX,0.95*halfPitchY)),
  ball.refAntiYPos(CGeoPoint:new_local(0.7*halfPitchX,0.95*halfPitchY)),
}
local function projectX()
    local x = 0
    if(ball.posY()>0) then --170 -70
         if(ball.posX()>=170) then
            x = 16
            return x
         else
           x = -16
            return x 
         end
    else --170 70
          if(ball.posX()>=170) then
            x = 16
            return x
          else
           x = -16
            return x
          end
    end
end

local function projectY()
    local y = 0
    if(ball.posY()>0) then --170 -70
         if(ball.posX()>=170) then
            y = 16
            return y
         else
           y = 16
            return y
         end
    else --170 70
          if(ball.posX()>=170) then
            y = -16
            return y
          else
           y = -16
            return y
          end
    end
end

gPlayTable.CreatePlay{

firstState = "start",

["start"] = {
  switch = function()
		if cond.isGameOn() then
			return "exit"
		end	  
	end,
  --Assister = task.goCmuRush(ball.pos())
  Assister = task.goCmuRush(pos.reflectPos(projectX(),-projectY()),_,_,flag.allow_dss),
  Leader   = task.goCmuRush(LEADER_POS[1],_,_,flag.allow_dss),
  Special  = task.goCmuRush(SPECIAL_POS[1],_,_,flag.allow_dss),
 Defender = task.goCmuRush(READY_POS,_,_,flag.allow_dss),
  Middle   = task.goCmuRush(MIDDLE_POS[3],_,_,flag.allow_dss),
  Goalie   = task.goCmuRush(PENALTY_POS,_,_,flag.allow_dss),
  match    = "{A}{L}{D}{MS}"
},

name = "Ref_Stop4FrontKick",
applicable = {
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
