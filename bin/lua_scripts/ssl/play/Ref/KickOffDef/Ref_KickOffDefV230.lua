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
	Leader   = task.goCmuRush(CGeoPoint:new_local(-70, -60),_,flag.allow_dss), --task.goSpeciPos(KICKOFF_DEF_POS("left")),
	Special  = task.goCmuRush(CGeoPoint:new_local(-70, 60),_,flag.allow_dss), --task.goSpeciPos(KICKOFF_DEF_POS("right")),
	Assister = task.goCmuRush(CGeoPoint:new_local(-70, 0),_,flag.allow_dss),
	Middle   = task.leftBack(),
	Defender = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[ADMLS]"
},

name = "Ref_KickOffDefV230",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
