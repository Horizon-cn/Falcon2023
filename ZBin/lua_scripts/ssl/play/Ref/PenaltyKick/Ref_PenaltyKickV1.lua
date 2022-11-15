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
	Leader  = task.goLeftSupport(),
	Assister = task.goRightSupport(),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Kicker  = task.stop(),
	match = "{L}{ADM}"
},

["gotoshort"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < 30 , 10 , 120) then
			return "tempshort"
		end
	end,
	Goalie = task.goalie(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(460,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(460,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(450,0),player.toBallDir),
	match = "{L}{ADM}"
},

["tempshort"] = {
	switch = function ()
		if bufcnt(cond.isNormalStart()) then
			return "shoot"
		end
	end,
	Goalie = task.goalie(),
	Leader  = task.goCmuRush(CGeoPoint:new_local(460,-100)),
	Assister = task.goCmuRush(CGeoPoint:new_local(460,100)),
	Middle  = task.leftBack(),
	Defender = task.rightBack(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(450,0),player.toBallDir),
	match = "{L}{ADM}"
},

["shoot"] = {
	switch = function ()
		if bufcnt(ball.refPosX()<550 , 350 , 400) or ball.posX() > 550 then
			return "forceshoot"
		end
	end,
	Leader  = task.stop(),
	Middle  = task.stop(),
	Crosser = task.stop(),
	Defender = task.stop(),
	Assister = task.stop(),
	Kicker  = task.shootV2(CGeoPoint:new_local(605,-50)),
	match = "{LADM}"
},

["forceshoot"] = {
	switch = function ()
		if ball.posX() > 550 then
			return "exit"
		end
	end,
	Leader  = task.stop(),
	Middle  = task.stop(),
	Crosser = task.stop(),
	Defender = task.stop(),
	Assister = task.stop(),
	Kicker  = task.shootV2(CGeoPoint:new_local(605,50)),
	match = "{LADM}"
},

["gotolong"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Kicker") < 30 , 10 , 120) then
			return "templong"
		end
	end,
	Goalie = task.goalie(),
	Leader  = task.stop(),
	Middle  = task.stop(),
	Defender = task.stop(),
	Assister = task.stop(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(-320,0)),
	match = "{L}{ADM}"
},

["templong"] = {
	switch = function ()
		if bufcnt(cond.isNormalStart()) then
			return "kick"
		end
	end,
	Goalie = task.goalie(),
	Leader  = task.stop(),
	Middle  = task.stop(),
	Defender = task.stop(),
	Assister = task.stop(),
	Kicker  = task.goCmuRush(CGeoPoint:new_local(-320,0)),
	match = "{L}{ADM}"
},

["kick"] = {
	switch = function ()
		if ball.posX() > 400 then
			return "exit"
		end
	end,
	Goalie = task.goalie(),
	Leader  = task.stop(),
	Middle  = task.stop(),
	Defender = task.stop(),
	Assister = task.stop(),
	Kicker  = task.goAndTurnKick(),
	match = "{LADM}"
},

name = "Ref_PenaltyKickV1",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
