gPlayTable.CreatePlay{

firstState = "run1",
["run1"] = {
	switch = function ()
		if true then
			return "run1";
		end
	end,
    Kicker = task.chaseNew(),

    match = ""
},

name = "Test_ChaseNew",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}