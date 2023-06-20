-- 角球定位球在一开始就进行站位
-- by zhyaic 2014-04-08
-- yys 2015-06-10

local STOP_FLAG  = bit:_or(flag.slowly, flag.dodge_ball)
local STOP_DSS   = bit:_or(flag.dodge_ball, flag.allow_dss)
local KICK_POS   = function ()
	return ball.syntYPos(CGeoPoint:new_local(ball.posX() - 59, param.pitchWidth/2-18))()
end

local KICK_DIR  = ball.antiYDir(1.57)

local MIDDLE_POS = ball.antiYPos(CGeoPoint:new_local(190, -50))

local FRONT_POS1 = ball.antiYPos(CGeoPoint:new_local(400, 150))
local FRONT_POS2 = ball.antiYPos(CGeoPoint:new_local(300, 75))
local FRONT_POS3 = ball.antiYPos(CGeoPoint:new_local(300, -200))

local ACC = 300

local WAIT_BALL_POS   = function ()
  return ball.pos() + Utils.Polar2Vector(50, ball.syntY(0.5 * math.pi))
end
local RECEIVE_POS = ball.syntYPos(CGeoPoint:new_local(200, 100))

gPlayTable.CreatePlay{

firstState = "start",

["start"] = {
	switch = function()
		if cond.isGameOn() then
			return "exit"
		end	  
	end,
	Assister = task.goCmuRush(WAIT_BALL_POS,_,_,flag.allow_dss + flag.dodge_ball),--4
    Leader   = task.markingFront("First"),
    Middle   = task.markingFront("Second"),
    Special  = task.multiBack(3,1),
    Defender = task.multiBack(3,2),
    Breaker  = task.multiBack(3,3),
    Crosser  = task.defendHead(),
    Goalie   = task.goalieNew(),
    match = "{D}{A}{B}{S}{LCM}"
},

name = "Ref_Stop4CornerKick_normal",
applicable = {
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}