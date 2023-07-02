gPlayTable.CreatePlay{
firstState = "init",

["init"] = {
	switch = function ()
		if false then
			return "exit"
		end
	end,
	Leader  = task.goCmuRush(CGeoPoint:new_local(300/1200*param.pitchLength,250/900*param.pitchWidth),_,_,flag.allow_dss),
	Middle  = task.goCmuRush(CGeoPoint:new_local(300/1200*param.pitchLength,-250/900*param.pitchWidth),_,_,flag.allow_dss),
	Crosser = task.goCmuRush(CGeoPoint:new_local(300/1200*param.pitchLength,-200/900*param.pitchWidth),_,_,flag.allow_dss),
	Defender = task.goCmuRush(CGeoPoint:new_local(300/1200*param.pitchLength,200/900*param.pitchWidth),_,_,flag.allow_dss),
	Assister = task.goCmuRush(CGeoPoint:new_local(300/1200*param.pitchLength,225/900*param.pitchWidth),_,_,flag.allow_dss),
	Breaker = task.goCmuRush(CGeoPoint:new_local(300/1200*param.pitchLength,-225/900*param.pitchWidth),_,_,flag.allow_dss),
	Engine = task.goCmuRush(CGeoPoint:new_local(300/1200*param.pitchLength,175/900*param.pitchWidth),_,_,flag.allow_dss),
	Goalie   = task.goalieNew("penalty"),
	match = "{CD}{AB}{LME}"
},

name = "Ref_PenaltyDef8",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
