gPlayTable.CreatePlay{

firstState = "goalie",

["goalie"] = {
	switch = function ()
		if true then
			return "goalie";
		end
	end,
	Defender = task.leftBack(),
    Assister = task.advanceV4(),
    Goalie = task.goalieNew(),
    match=""
    --match = "[AD]"
},

name = "Test_Goalie",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}