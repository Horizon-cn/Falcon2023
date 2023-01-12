
gPlayTable.CreatePlay{

firstState = "test",

["test"] = {
	switch = function ()
		if bufcnt(true , 100) then
			return "test";
		end
	end,
    Kicker = task.timeDelayTest(),
    match = ""
},

name = "Test_TimeDelayTest",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}