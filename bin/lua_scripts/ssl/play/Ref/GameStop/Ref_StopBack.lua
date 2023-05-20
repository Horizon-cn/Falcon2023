gPlayTable.CreatePlay{

firstState = "start",

["start"] = {
	switch = function()
		if cond.isGameOn() then
			return "exit"
		end	  
	end,
	Assister = task.defendHead(),
	Special  = task.defendMiddle(),
	Leader   = task.sideBack(),
	Middle   = task.leftBack(),
	Defender = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[ALSMD]"
},

name = "Ref_StopBack",
applicable = {
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}