gPlayTable.CreatePlay{

firstState = "goalie",

["goalie"] = {
	switch = function ()
		if true then
			return "goalie";
		end
	end,
	-- Defender = task.multiBack(3,1),
 --    Assister = task.multiBack(3,2),
 --    Hawk = task.multiBack(3,3),
    Goalie = task.chaseNew(),
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