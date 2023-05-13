gPlayTable.CreatePlay{
firstState = "init",

["init"] = {
	switch = function ()
		if bufcnt(1,1,50) then
			return "start"
		end
	end,
	Leader  = task.goCmuRush(CGeoPoint:new_local(265, 250),_,_,flag.allow_dss),
	Middle  = task.goCmuRush(CGeoPoint:new_local(265,-250),_,_,flag.allow_dss),
	Crosser = task.goCmuRush(CGeoPoint:new_local(265,-200),_,_,flag.allow_dss),
	Defender = task.goCmuRush(CGeoPoint:new_local(265,200),_,_,flag.allow_dss),
	Assister = task.goCmuRush(CGeoPoint:new_local(265,225),_,_,flag.allow_dss),
	Goalie   = task.penaltyGoalie(),
	match = "{LACDM}"
},


["start"] = {
	switch = function ()
		if cond.isNormalStart() then
			return "kicklong"
		end
	end,
	Leader  = task.goCmuRush(CGeoPoint:new_local(265, 250),_,_,flag.allow_dss),
	Middle  = task.goCmuRush(CGeoPoint:new_local(265,-250),_,_,flag.allow_dss),
	Crosser = task.goCmuRush(CGeoPoint:new_local(265,-200),_,_,flag.allow_dss),
	Defender = task.goCmuRush(CGeoPoint:new_local(265,200),_,_,flag.allow_dss),
	Assister = task.goCmuRush(CGeoPoint:new_local(265,225),_,_,flag.allow_dss),
	Goalie   = task.penaltyGoalie(),
	match    = "{LACDM}"
},

["kicklong"] = {
	switch = function ()
		if false then
			return "exit"
		end
	end,
	Leader  = task.goCmuRush(CGeoPoint:new_local(265, 250),_,_,flag.allow_dss),
	Middle  = task.goCmuRush(CGeoPoint:new_local(265,-250),_,_,flag.allow_dss),
	Crosser = task.goCmuRush(CGeoPoint:new_local(265,-200),_,_,flag.allow_dss),
	Defender = task.goCmuRush(CGeoPoint:new_local(265,200),_,_,flag.allow_dss),
	Assister = task.goCmuRush(CGeoPoint:new_local(265,225),_,_,flag.allow_dss),
	Goalie  = task.advance(),
	match = "{LACDM}"
},

name = "Ref_PenaltyDefV6",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
