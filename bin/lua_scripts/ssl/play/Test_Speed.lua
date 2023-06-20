local START_POS,END_POS
START_POS=CGeoPoint(0,0)
END_POS=CGeoPoint(300,300)
local SPEED_BEGIN,SPEED_END,SPEED_STEP
SPEED_BEGIN=200
SPEED_END=400
SPEED_STEP=50

gPlayTable.CreatePlay{

firstState = "test",

["test"] = {
	switch = function ()
		if true then
			return "test";
		end
	end,
    Kicker = task.speedTest(START_POS,END_POS,SPEED_BEGIN,SPEED_END,SPEED_STEP),
    match=""
},

name = "Test_Speed",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}