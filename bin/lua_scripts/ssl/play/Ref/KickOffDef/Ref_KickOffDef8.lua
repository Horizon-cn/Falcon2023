local function KICKOFF_DEF_POS(str)
	return function()
		local x, y
		x, y = CKickOffDefPos(str)
		return CGeoPoint:new_local(x,y)
	end
end

local guardpoint = CGeoPoint:new_local(-100,0)
gPlayTable.CreatePlay{
firstState = "start",

["start"] = {
	switch = function ()
		if cond.isGameOn(5) then
			return "exit"
		end
	end,
	Leader   = task.goCmuRush(guardpoint), --task.goSpeciPos(KICKOFF_DEF_POS("left")),
	Assister = task.multiBack(4,1),
	Special  = task.multiBack(4,2),
	Middle   = task.multiBack(4,3),
	Defender = task.multiBack(4,4),
	Goalie   = task.goalieNew(),
	match    = "[ADMLS]"
},



name = "Ref_KickOffDef8",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
