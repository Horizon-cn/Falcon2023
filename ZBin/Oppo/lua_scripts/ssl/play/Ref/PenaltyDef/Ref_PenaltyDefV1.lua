
gPlayTable.CreatePlay{
firstState = "init",

["init"] = {
	switch = function ()
		if bufcnt(1,50) then
			return "start"
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


["start"] = {
	switch = function ()
		if cond.isNormalStart() then
			if player.toBallDist("Goalie")>400 then
				return "kicklong"
			else
				return "kickshort"
			end
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
		if false then
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
