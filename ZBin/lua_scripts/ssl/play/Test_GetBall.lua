local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling
local TargetPos  = CGeoPoint:new_local(300,425)
local distThreshold = 50

gPlayTable.CreatePlay{

firstState = "getball",

-- ["getball"] = {
-- 	switch = function ()
-- 		if true then
-- 			return "getball";
-- 		end
-- 	end,
-- 	--Receiver = task.goRightSupport(),
-- 	Leader = task.getBall(),
--     match = "[L]"
-- },

["getball"] = {
	switch = function ()
		if true then
			return "getball";
		end
	end,
	--Receiver = task.goRightSupport(),
	Leader = task.receivePass(TargetPos, 30),
    match = "[L]"
},

name = "Test_GetBall",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}