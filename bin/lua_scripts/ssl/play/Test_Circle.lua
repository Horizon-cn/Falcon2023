local TargetPos1  = CGeoPoint:new_local(250,150)
local TargetPos2  = CGeoPoint:new_local(250,-150)
local TargetPos3  = CGeoPoint:new_local(0,9)
local TargetPos4  = CGeoPoint:new_local(-250,150)
local radius = 50
local opt = 1

local DIR1  = 1.57
local DIR2  = 1.57
local DIR3  = 1.57
local DIR4  = 1.57

local distThreshold = 50
local ACC = nil

gPlayTable.CreatePlay{

firstState = "Run",

["Run"] = {
	switch = function ()
		if true then
			return "Run";
		end
	end,
    Goalie = task.goPIDCircle(TargetPos3, radius, opt),
    match = ""
},

name = "Test_Circle",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}