gPlayTable.CreatePlay{

firstState = "support",

["support"] = {
	switch = function ()
		if true then
			return "support";
		end
	end,
    Leader = task.stop(), --task.advance(), --task.advanceV4(),
    Special = task.support("Leader", 1), --task.goRightSupport(),
	Middle = task.support("Leader", 0), --task.goLeftSupport(),
    Defender = task.leftBack(),
    Assister = task.rightBack(),
    Goalie   = task.goalieNew(),
    Powerhouse = task.support("Leader", 2), --task.leftCenterBack(),
    Hawk = task.support("Leader", 3), --task.rightCenterBack(),
    --match = ""
	match    = "[L][MSPH][AD]"
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