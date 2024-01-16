gPlayTable.CreatePlay{

firstState = "run1",
["run1"] = {
	switch = function ()
		if true then
			return "run1";
		end
	end,
    Kicker = task.testBreak(CGeoPoint:new_local(450,0)),

    match = ""
},

name = "Test_Break",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}