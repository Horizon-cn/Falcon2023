gPlayTable.CreatePlay{

firstState = "run1",
["run1"] = {
	switch = function ()
		if true then
			return "run1";
		end
	end,
    Kicker = task.getBall(ball.pos()),

    match = ""
},

name = "Test_GetBall",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}