-- 角球定位球在一开始就进行站位
-- by zhyaic 2014-04-08
-- yys 2015-06-10

local STOP_FLAG  = bit:_or(flag.slowly, flag.dodge_ball)
local STOP_DSS   = bit:_or(flag.dodge_ball, flag.allow_dss)
local KICK_POS   = function ()
	return ball.syntYPos(CGeoPoint:new_local(ball.posX() - 59, param.pitchWidth/2-18))()
end

local KICK_DIR  = ball.antiYDir(1.57)
local FRONT_POS1=CGeoPoint()
local ACC=500;

gPlayTable.CreatePlay{
 
firstState = "start",

["start"] = {
	switch = function()
		if cond.isGameOn() then
			return "exit"
		end	  
	end,
	Assister = task.goCmuRush(KICK_POS, KICK_DIR, ACC, STOP_DSS),
	Leader   = task.goCmuRush(FRONT_POS1, _, ACC, STOP_DSS),
	Middle   = task.goCmuRush(FRONT_POS2, _, ACC, STOP_DSS),
	Special  = task.goCmuRush(FRONT_POS3, _, ACC, STOP_DSS),
	match    = "[A][L][M][S]"
},

name = "Ref_Stop4CornerKick",
applicable = {
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}