local function KICKOFF_DEF_POS(str)
	return function()
		local x, y
		x, y = CKickOffDefPos(str)
		return CGeoPoint:new_local(x,y)
	end
end

gPlayTable.CreatePlay{
firstState = "start",

["start"] = {
	switch = function ()
		if cond.isGameOn(5) then
			return "exit"
		end
	end,
	Leader   = task.goSpeciPos(CGeoPoint:new_local(-100, -30)), --task.goSpeciPos(KICKOFF_DEF_POS("left")),
	Special  = task.goSpeciPos(CGeoPoint:new_local(-100, 30)), --task.goSpeciPos(KICKOFF_DEF_POS("right")),
	Assister = task.goSpeciPos(CGeoPoint:new_local(-100, 0)),
	Middle   = task.rightBack(),
	Defender = task.leftBack(),
	Hawk     = task.marking("First"),
	Powerhouse = task.marking("Second"),
	Goalie   = task.goalieNew(),
	match    = "[ADMLSHP]"
},

name = "Ref_KickOffDefV1",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
