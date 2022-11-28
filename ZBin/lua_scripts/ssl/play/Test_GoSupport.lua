gPlayTable.CreatePlay{

firstState = "support",

["support"] = {
	switch = function ()
		if true then
			return "support";
		end
	end,
    Leader = task.advanceV4(),
    Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
    Defender = task.leftBack(),
    Assister = task.rightBack(),
    Goalie   = task.goalieNew(),
    --Breaker = task.leftCenterBack(),
    --Crosser = task.rightCenterBack(),
    --match = ""
	match    = "[L][MS][AD]"
	-- match = "[MS]"
},

name = "Test_GoSupport",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}