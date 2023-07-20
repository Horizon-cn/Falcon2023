local TargetPos=CGeoPoint:new_local(200,0)

gPlayTable.CreatePlay{

firstState = "start",
["start"] = {
	switch = function ()
		if true then
			return "start";
		end
	end,
	Leader = task.rush(TargetPos),
    match = "[L]"
},
name = "Test_Rush",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}