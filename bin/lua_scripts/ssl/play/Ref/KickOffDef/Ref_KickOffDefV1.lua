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
	Leader   = task.goSpeciPos(CGeoPoint:new_local(-100, -30),_,flag.allow_dss), --task.goSpeciPos(KICKOFF_DEF_POS("left")),
	Special  = task.goSpeciPos(CGeoPoint:new_local(-100, 30),_,flag.allow_dss), --task.goSpeciPos(KICKOFF_DEF_POS("right")),
	Assister = task.goSpeciPos(CGeoPoint:new_local(-100, 0),_,flag.allow_dss),
	Middle   = task.multiBack(3, 1),
	Defender = task.multiBack(3, 2),
	Hawk     = task.multiBack(3, 3), --task.marking("First"),
	Powerhouse = task.goSpeciPos(CGeoPoint:new_local(-300, -200),_,flag.allow_dss), --task.marking("Second"),
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
