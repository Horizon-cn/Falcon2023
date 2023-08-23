gPlayTable.CreatePlay{

firstState = "goalie",

["goalie"] = {
	switch = function ()
		if true then
			return "goalie";
		end
	end,
	Powerhouse = task.advance(),
	Defender_Assister_Hawk = combo.multiBack(3),
	Finisher = task.sideBackUltra(),
	Goalie = task.goalieNew(),
    match="[P][ADH]",
},

name = "Test_Goalie",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
