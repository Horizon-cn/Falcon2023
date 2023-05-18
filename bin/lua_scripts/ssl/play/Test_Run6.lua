local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_NOT_AVOID --+ flag.dribbling

local TargetPos1  = CGeoPoint:new_local(50,-220)
local TargetPos2  = CGeoPoint:new_local(50,-140)
local TargetPos3  = CGeoPoint:new_local(50,-70)
local TargetPos4  = CGeoPoint:new_local(50,0)
local TargetPos5  = CGeoPoint:new_local(50,70)
local TargetPos6  = CGeoPoint:new_local(50,140)

local TargetPos7  = CGeoPoint:new_local(310,-220)
local TargetPos8  = CGeoPoint:new_local(310,-140)
local TargetPos9  = CGeoPoint:new_local(310,-70)
local TargetPos10  = CGeoPoint:new_local(310,0)
local TargetPos11  = CGeoPoint:new_local(310,70)
local TargetPos12  = CGeoPoint:new_local(310,140)

local DIR1  = 1.57
local DIR2  = 1.57
local DIR3  = 1.57
local DIR4  = 1.57

local distThreshold = 10
local ACC = nil


-- Leader + Assister 
-- Middle
-- Goalie + Special + Defender
gPlayTable.CreatePlay{

firstState = "run1",

--front
["run1"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Leader") < distThreshold , 150, 1000) then
			return "run2";
		end
	end,
	Leader = task.goCmuRush(TargetPos1, 0),
	Assister = task.goCmuRush(TargetPos2, 0),
	Middle = task.goCmuRush(TargetPos3, 0),
    Special = task.goCmuRush(TargetPos4, 0),
	Defender = task.goCmuRush(TargetPos5, 0),
	Goalie = task.goCmuRush(TargetPos6, 0),
    match = "[L][DA][MS]"
},

["run2"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Leader") < distThreshold , 150, 1000) then
			return "run1";
		end
	end,
	Leader = task.goCmuRush(TargetPos7, 0),
	Assister = task.goCmuRush(TargetPos8, 0),
	Middle = task.goCmuRush(TargetPos9, 0),
    Special = task.goCmuRush(TargetPos10, 0),
	Defender = task.goCmuRush(TargetPos11, 0),
	Goalie = task.goCmuRush(TargetPos12, 0),
    match = "[L][DA][MS]"
},

name = "Test_Run6",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
