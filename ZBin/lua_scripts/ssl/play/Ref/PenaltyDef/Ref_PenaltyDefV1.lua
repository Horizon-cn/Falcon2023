gPlayTable.CreatePlay{
firstState = "init",

["init"] = {
	switch = function ()
		if bufcnt(ball.refPosX()>400) then
			return "startlong"
		else
			return "startshort"
		end
	end,
	Goalie = task.penaltyGoalie(),
	Leader  = task.goLWPassPos(),
	Assister = task.goRWPassPos(),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(450,0),player.toBallDir),
	Engine   = task.goLMPassPos(),
    Hawk     = task.goRMPassPos(),
	match = "{L}{ADM}{EH}"
},


["start"] = {
	switch = function ()
		if cond.isNormalStart() then
			return "kick"
		elseif cond.isGameOn() then
			return "exit"
		end
	end,
	Leader  = task.goCmuRush(CGeoPoint:new_local(430, 180)),
	Middle  = task.goCmuRush(CGeoPoint:new_local(430,150)),
	Crosser = task.goCmuRush(CGeoPoint:new_local(430,-150)),
	Defender = task.goCmuRush(CGeoPoint:new_local(430,-250)),
	Assister = task.goCmuRush(CGeoPoint:new_local(430,250)),
	Goalie   = task.penaltyGoalie(),
	match    = "{LACDM}"
},

["kick"] = {
	switch = function ()
		if ball.posX() < -400 then
			return "exit"
		end
	end,
	Leader  = task.goCmuRush(CGeoPoint:new_local(430, 180)),
	Middle  = task.goCmuRush(CGeoPoint:new_local(430,150)),
	Crosser = task.goCmuRush(CGeoPoint:new_local(430,-150)),
	Defender = task.goCmuRush(CGeoPoint:new_local(430,-250)),
	Assister = task.goCmuRush(CGeoPoint:new_local(430,250)),
	Goalie  = task.penaltyGoalie(),
	match = "{LACDM}"
},

name = "Ref_PenaltyDefV1",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
