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
	Leader   = task.goSpeciPos(KICKOFF_DEF_POS("left")),
	Special  = task.goSpeciPos(KICKOFF_DEF_POS("right")),
	Assister = task.goSpeciPos(CGeoPoint:new_local(-100, 0)),
	Middle   = task.rightBack(),
	Defender = task.leftBack(),
	Goalie   = task.goalie(),
	match    = "[ADMLS]"
},

name = "Ref_KickOffDefV1",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
