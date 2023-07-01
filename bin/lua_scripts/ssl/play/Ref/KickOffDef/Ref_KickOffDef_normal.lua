-- local function KICKOFF_DEF_POS(str)
-- 	return function()
-- 		local x, y
-- 		x, y = CKickOffDefPos(str)
-- 		return CGeoPoint:new_local(x,y)
-- 	end
-- end
local UpPoint = CGeoPoint:new_local(-224,-140)
local MiddlePoint = CGeoPoint:new_local(-66,0)
local BelowPoint = CGeoPoint:new_local(-224,140)
gPlayTable.CreatePlay{
firstState = "start",

["start"] = {
	switch = function ()
		if cond.isGameOn(5) then
			return "exit"
		end
	end,
	--三個在圓外，剩下MultiBack
	Leader   = task.goCmuRush(MiddlePoint), --task.goSpeciPos(KICKOFF_DEF_POS("left")),
	Assister = task.goCmuRush(BelowPoint),	
	Special  = task.goCmuRush(UpPoint),
	Middle   = task.multiBack(4,1),
	Defender = task.multiBack(4,2),
	Breaker  = task.multiBack(4,3),
	Crosser  = task.multiBack(4,4),
	Goalie   = task.goalieNew(),
	match    = "[L][MD][AS][BC]"
},



name = "Ref_KickOffDef_normal",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
