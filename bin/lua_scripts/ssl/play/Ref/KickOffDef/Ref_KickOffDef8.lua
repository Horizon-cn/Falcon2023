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
	Assister = task.multiBack(6,1),
	Special  = task.multiBack(6,2),
	Middle   = task.multiBack(6,3),
	Defender = task.multiBack(6,4),
	Breaker  = task.multiBack(6,5),
	Crosser  = task.multiBack(6,6),
	Goalie   = task.goalieNew(),
	match    = "[L][ADMSBC]"
},



name = "Ref_KickOffDef8",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
