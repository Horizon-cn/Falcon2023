gPlayTable.CreatePlay{
firstState = "init",

["init"] = {
	switch = function ()
		if false then
			return "exit"
		end
	end,
	Leader  = task.goCmuRush(CGeoPoint:new_local(300, 250),_,_,flag.allow_dss),
	Middle  = task.goCmuRush(CGeoPoint:new_local(300,-250),_,_,flag.allow_dss),
	Crosser = task.goCmuRush(CGeoPoint:new_local(300,-200),_,_,flag.allow_dss),
	Defender = task.goCmuRush(CGeoPoint:new_local(300,200),_,_,flag.allow_dss),
	Assister = task.goCmuRush(CGeoPoint:new_local(300,225),_,_,flag.allow_dss),
	Breaker = task.goCmuRush(CGeoPoint:new_local(300,-225),_,_,flag.allow_dss),
	Engine = task.goCmuRush(CGeoPoint:new_local(300,175),_,_,flag.allow_dss),
	Goalie   = task.goalieNew("penalty"),
	match = "{LACDMBE}"
},

name = "Ref_PenaltyDef8",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
