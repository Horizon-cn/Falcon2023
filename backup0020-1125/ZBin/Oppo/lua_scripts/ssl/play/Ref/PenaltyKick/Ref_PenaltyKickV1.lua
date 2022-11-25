
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
	Leader  = task.goLWPassPos("Kicker"),
	Assister = task.goRWPassPos("Kicker"),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(450,0),player.toBallDir),
	Engine   = task.goLMPassPos("Kicker"),
    Hawk     = task.goRMPassPos("Kicker"),
	match = "{L}{ADM}{EH}"
},

["gotoshort"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < 30 , 10 , 120) then
			return "tempshort"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(450,0),player.toBallDir),
	Engine   = task.goCmuRush(CGeoPoint:new_local(440,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(440,150)),
	match = "{L}{ADM}{EH}"
},

["tempshort"] = {
	switch = function ()
		if bufcnt(cond.isNormalStart()) then
			return "rotate1"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(450,0),0.33),
	Engine   = task.goCmuRush(CGeoPoint:new_local(440,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(440,150)),
	match = "{L}{ADM}{EH}"
},

["rotate1"] = {
	switch = function ()
		if bufcnt(1,50,50) then
			return "rotate2"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(456,10),player.toBallDir),
	Engine   = task.goCmuRush(CGeoPoint:new_local(440,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(440,150)),
	match = "{L}{ADM}{EH}"
},

["rotate2"] = {
	switch = function ()
		if bufcnt(1,80,80) then
			return "rotate3"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(462,-10),player.toBallDir),
	Engine   = task.goCmuRush(CGeoPoint:new_local(440,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(440,150)),
	match = "{L}{ADM}{EH}"
},

["rotate3"] = {
	switch = function ()
		if bufcnt(1,80,80) then
			return "shoot"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(440,3),-0.33),
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
	Kicker  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.chaseNew(CGeoPoint:new_local(605,30)),
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
	Kicker  = task.goCmuRush(CGeoPoint:new_local(440,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(440,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.shootV2(CGeoPoint:new_local(605,55)),--
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
		if bufcnt(ball.refPosX()>500, 5, 10) then
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
