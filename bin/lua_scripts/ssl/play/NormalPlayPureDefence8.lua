gPlayTable.CreatePlay{

firstState = "PureDefence",

["PureDefence"] = {
	switch = function ()
		if true then
			return "PureDefence";
		end
	end,
	Leader   = task.marking("First"),
	Assister = task.marking("Second"),
    Middle   = task.multiBack(4,4),
    Special  = task.advance(),
	Defender = task.multiBack(4,1),
	Breaker  = task.multiBack(4,2),
	Crosser  = task.multiBack(4,3),
	Goalie   = task.goalieNew(),
    match = "[S][DBC][LMA]"
},

name = "NormalPlayPureDefence8",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
