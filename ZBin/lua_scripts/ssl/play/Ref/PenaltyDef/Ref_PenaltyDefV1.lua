
gPlayTable.CreatePlay{
firstState = "init",

["init"] = {
	switch = function ()
		if bufcnt(ball.refPosX()>0, 40, 50) then
			return "startlong"
		else
			return "startshort"
		end
	end,
	Leader  = task.goCmuRush(CGeoPoint:new_local(430, 180)),
	Middle  = task.goCmuRush(CGeoPoint:new_local(430,150)),
	Crosser = task.goCmuRush(CGeoPoint:new_local(430,-150)),
	Defender = task.goCmuRush(CGeoPoint:new_local(430,-250)),
	Assister = task.goCmuRush(CGeoPoint:new_local(430,250)),
	Engine   = task.goLMPassPos("Leader"),
    Hawk     = task.goRMPassPos("Leader"),
	Goalie   = task.penaltyGoalie(),
	match = "{LACDM}{EH}"
},


["startlong"] = {
	switch = function ()
		if bufcnt(cond.isGameOn(),20) then
			return "exit"
		elseif cond.isNormalStart() then
			return "kicklong"
		end
	end,
	Goalie   = task.goalieNew(),
	match    = "{LACDM}"
},

["startshort"] = {
	switch = function ()
		if bufcnt(cond.isGameOn(),20) then
			return "exit"
		elseif cond.isNormalStart() then
			return "kickshort"
		end
	end,
	Leader  = task.goCmuRush(CGeoPoint:new_local(430, 180)),
	Middle  = task.goCmuRush(CGeoPoint:new_local(430,150)),
	Crosser = task.goCmuRush(CGeoPoint:new_local(430,-150)),
	Defender = task.goCmuRush(CGeoPoint:new_local(430,-250)),
	Assister = task.goCmuRush(CGeoPoint:new_local(430,250)),
	Engine   = task.goLMPassPos("Leader"),
    Hawk     = task.goRMPassPos("Leader"),
	Goalie   = task.penaltyGoalie(),
	match    = "{LACDM}{EH}"
},

["kicklong"] = {
	switch = function ()
		if bufcnt(cond.isGameOn(),20) then
			return "exit"
		end
	end,
	Goalie  = task.goalieNew(),
	match = "{LACDM}{EH}"
},

["kickshort"] = {
	switch = function ()
		if bufcnt(cond.isGameOn(),20) then
			return "exit"
		end
	end,
	Leader  = task.goCmuRush(CGeoPoint:new_local(430, 180)),
	Middle  = task.goCmuRush(CGeoPoint:new_local(430,150)),
	Crosser = task.goCmuRush(CGeoPoint:new_local(430,-150)),
	Defender = task.goCmuRush(CGeoPoint:new_local(430,-250)),
	Assister = task.goCmuRush(CGeoPoint:new_local(430,250)),
	Engine   = task.goLMPassPos("Leader"),
    Hawk     = task.goRMPassPos("Leader"),
	Goalie  = task.penaltyGoalie(),
	match = "{LACDM}{EH}"
},

name = "Ref_PenaltyDefV1",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
