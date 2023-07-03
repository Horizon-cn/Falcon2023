gPlayTable.CreatePlay{

firstState = "goalie",

["goalie"] = {
	switch = function ()
		if true then
			return "goalie";
		end
	end,
	Powerhouse = task.advance(),
	Defender000Assister000Hawk = combo.multiBack(3),
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
