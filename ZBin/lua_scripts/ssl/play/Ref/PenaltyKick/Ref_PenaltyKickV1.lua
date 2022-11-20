local DSS = flag.not_dodge_penalty

gPlayTable.CreatePlay{

firstState = "init",

["init"] = {
	switch = function ()
		if bufcnt(ball.refPosX()<200) then
			return "gotolong"
		else
			return "gotoshort"
		end
	end,
	Goalie = task.goalie(),
	Leader  = task.goLWPassPos(),
	Assister = task.goRWPassPos(),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(450,0),player.toBallDir),
	Engine   = task.goLMPassPos(),
    Hawk     = task.goRMPassPos(),
	match = "{L}{ADM}{EH}"
},

["gotoshort"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < 30 , 10 , 120) then
			return "tempshort"
		end
	end,
	Goalie = task.goalie(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(450,0),player.toBallDir),
	Engine   = task.goCmuRush(CGeoPoint:new_local(440,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(440,150)),
	match = "{L}{ADM}{EH}"
},

["tempshort"] = {
	switch = function ()
		if bufcnt(cond.isNormalStart()) then
			return "shoot"
		end
	end,
	Goalie = task.goalie(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(450,0),player.toBallDir),
	Engine   = task.goCmuRush(CGeoPoint:new_local(440,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(440,150)),
	match = "{L}{ADM}{EH}"
},

["shoot"] = {
	switch = function ()
		if bufcnt(ball.refPosX()<550 , 450 , 500) or ball.posX() > 550 then
			return "forceshoot"
		end
	end,
	Goalie = task.goalie(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Kicker  = task.chaseNew(),
	Engine   = task.goCmuRush(CGeoPoint:new_local(440,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(440,150)),
	match = "{LADM}{EH}"
},

["forceshoot"] = {
	switch = function ()
		if ball.posX() > 550 then
			return "exit"
		end
	end,
	Goalie = task.goalie(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Kicker  = task.shootV2(CGeoPoint:new_local(605,55)),
	Engine   = task.goCmuRush(CGeoPoint:new_local(440,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(440,150)),
	match = "{LADM}{EH}"
},

["gotolong"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < 30 , 10 , 120) then
			return "templong"
		end
	end,
	Goalie  = task.goCmuRush(CGeoPoint:new_local(-260,0)),
	match = ""
},

["templong"] = {
	switch = function ()
		if bufcnt(cond.isNormalStart()) then
			return "kick"
		end
	end,
	Goalie  = task.goCmuRush(CGeoPoint:new_local(-260,0)),
	match = ""
},

["kick"] = {
	switch = function ()
		if ball.posX() > 400 then
			return "exit"
		end
	end,
	Goalie  = task.penaltykick(),
	match = ""
},

name = "Ref_PenaltyKickV1",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}