local WAIT_POS1=CGeoPoint:new_local(-200/1200*param.pitchLength,100/900*param.pitchWidth)
local WAIT_POS2=CGeoPoint:new_local(-200/1200*param.pitchLength,-100/900*param.pitchWidth)
local guardpoint = CGeoPoint:new_local(-88/1200*param.pitchLength,0/900*param.pitchWidth)

gPlayTable.CreatePlay{
firstState = "start",

["start"] = {
	switch = function ()
		if cond.isGameOn(5) then
			return "exit"
		end
	end,
	Leader   = task.goCmuRush(guardpoint),
	Assister = task.multiBack(6,1),
	Special  = task.multiBack(6,2),
	Middle   = task.multiBack(6,3),
	Defender = task.multiBack(6,4),
	Breaker  = task.goCmuRush(WAIT_POS1,_,_,flag.allow_dss + flag.dodge_ball),
	Crosser  = task.goCmuRush(WAIT_POS2,_,_,flag.allow_dss + flag.dodge_ball),
	Goalie   = task.goalieNew(),
	match    = "[L][ADMS][BC]"
},



name = "Ref_KickOffDef_PureDefence8",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
