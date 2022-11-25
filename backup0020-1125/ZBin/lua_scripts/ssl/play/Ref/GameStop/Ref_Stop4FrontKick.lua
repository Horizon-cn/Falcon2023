-- 前场球定位球在stop阶段进行站位
-- FanHao 2022-10-26

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

local ACC = 300

gPlayTable.CreatePlay{

firstState = "start",

["start"] = {
	switch = function()
		if cond.isGameOn() then
			return "exit"
		end	  
	end,
	print("Engine:"..gRoleNum["Engine"]),
	print("Assister:"..gRoleNum["Assister"]),

	Assister = task.goCmuRush(KICK_POS, SHOOT_DIR, ACC, STOP_DSS),
	--Special  = task.goCmuRush(READY_POS, _, ACC, STOP_DSS),
	Special  = task.goCmuRush(READY_POS_1, _, ACC, STOP_DSS),
	Leader   = task.goCmuRush(READY_POS_2, _, ACC, STOP_DSS),
	Middle  = task.goCmuRush(READY_POS, _, ACC, STOP_DSS),
	--Middle   = task.goCmuRush(READY_POS_1, _, ACC, STOP_DSS),
	Defender = task.leftBack(),
	Goalie   = task.goalieNew(),
	Engine	 = task.goCmuRush(FRONT_POS, _, ACC, STOP_DSS),
	Hawk 	 = task.rightBack(),
	match    = "[AMLDSEH]"
},

name = "Ref_Stop4FrontKick",
applicable = {
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
