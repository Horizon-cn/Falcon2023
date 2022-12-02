local function dir__dead()
	local function dir_dead_inside(runner)
		return (CGeoPoint:new_local(600,50)-ball.pos()):dir()
	end
	return dir_dead_inside
end

gPlayTable.CreatePlay{

firstState = "init",

["init"] = {
	switch = function ()
		if bufcnt(ball.posX()<200) then
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
	Kicker  = task.goCmuRush(CGeoPoint:new_local(420,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(420,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(450,0),player.toBallDir),
	Engine   = task.goCmuRush(CGeoPoint:new_local(420,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(420,150)),
	match = "{L}{ADM}{EH}"
},

["tempshort"] = {
	switch = function ()
		if bufcnt(cond.isNormalStart()) then
			return "forceshoot"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(420,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(420,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(450,0),0.0),
	Engine   = task.goCmuRush(CGeoPoint:new_local(420,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(420,150)),
	match = "{L}{ADM}{EH}"
},

["rotate1"] = {
	switch = function ()
		if bufcnt(1,50,50) then
			return "rotate2"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(420,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(420,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(455,0),player.toBallDir),
	Engine   = task.goCmuRush(CGeoPoint:new_local(420,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(420,150)),
	match = "{L}{ADM}{EH}"
},

["rotate2"] = {
	switch = function ()
		if bufcnt(1,80,80) then
			return "rotate3"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(420,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(420,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(460,0),player.toBallDir),
	Engine   = task.goCmuRush(CGeoPoint:new_local(420,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(420,150)),
	match = "{L}{ADM}{EH}"
},

["rotate3"] = {
	switch = function ()
		if bufcnt(1,80,80) then
			return "shoot"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(420,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(420,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(465,0),player.toBallDir),
	Engine   = task.goCmuRush(CGeoPoint:new_local(420,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(420,150)),
	match = "{L}{ADM}{EH}"
},


["shoot"] = {
	switch = function ()
		if bufcnt(ball.posX()<550 , 350 , 400) then
			return "forceshoot"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(420,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(420,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.chaseNew(),
	Engine   = task.goCmuRush(CGeoPoint:new_local(420,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(420,150)),
	match = "{LADM}{EH}"
},

["forceshoot"] = {
	switch = function ()
		if bufcnt(ball.posX()<550 , 250 , 300) then
			return "forceforceshoot"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(420,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(420,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.goAndTurnKick(dir__dead,650),
	Engine   = task.goCmuRush(CGeoPoint:new_local(420,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(420,150)),
	match = "{LADM}{EH}"
},

["forceforceshoot"] = {
	switch = function ()
		if ball.posX() > 550 then
			return "exit"
		end
	end,
	Goalie = task.goalie(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(420,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(420,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Leader  = task.penaltykickshort(),
	Engine   = task.goCmuRush(CGeoPoint:new_local(420,-150)),
    Hawk     = task.goCmuRush(CGeoPoint:new_local(420,150)),
	match = "{LADM}{EH}"
},

["gotolong"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Goalie") < 30 , 10 , 120) then
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
	Goalie  = task.goCmuRush(CGeoPoint:new_local(-210,0)),
	match = ""
},

["kick"] = {
	switch = function ()
		if ball.posX()>500 then
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
