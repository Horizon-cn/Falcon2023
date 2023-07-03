local Farpos = function()
	if  ball.posX() > -265 and ball.posY()<150 and ball.posY()> -150 then
		return ball.refSyntYPos(CGeoPoint:new_local(-130,275))()
	else
		return ball.refAntiYPos(CGeoPoint:new_local(-130,275))()
	end
end

local Nearpos = function()
	if  ball.posX() > -265 and ball.posY()<150 and ball.posY()> -150 then
		return ball.refSyntYPos(CGeoPoint:new_local(-60,110))()
	else
		return ball.refAntiYPos(CGeoPoint:new_local(-60,110))()
	end
end

local chippos = function()
	if  ball.posX() > -265 and ball.posY()<150 and ball.posY()> -150 then
		return ball.refAntiYPos(CGeoPoint:new_local(0,300))()
	else
		return  ball.refSyntYPos(CGeoPoint:new_local(0,300))()
	end
end

local helppos = function()
	if  ball.posX() > -265 and ball.posY()<150 and ball.posY()> -150 then
		return ball.refAntiYPos(CGeoPoint:new_local(-270,390))()
	else
		return ball.refSyntYPos(CGeoPoint:new_local(-270,390))()
	end
end

local assipos = function()
	if  ball.posX() > -265 and ball.posY()<150 and ball.posY()> -150 then
		return ball.refAntiYPos(CGeoPoint:new_local(95,190))()
	else
		return ball.refSyntYPos(CGeoPoint:new_local(95,190))()
	end
end

local getpos  = function()
	if  ball.posX() > -265 and ball.posY()<150 and ball.posY()> -150 then
		return ball.refAntiYPos(CGeoPoint:new_local(125,340))()
	else
		return ball.refSyntYPos(CGeoPoint:new_local(125,340))()
	end
end

local Blockpos = function()
	if ball.posX() > -265 and ball.posY()<150 and ball.posY()> -150 then
		return ball.refSyntYPos(CGeoPoint:new_local(90,-310))()
	else
		return ball.refAntiYPos(CGeoPoint:new_local(90,-310))()
	end
end

gPlayTable.CreatePlay{

firstState = "startball",

["startball"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Breaker") < 30, "fast") then
			return "changepos"
		elseif bufcnt(true, 300) then
			return "Shootball"
		end
	end,
	Assister = task.staticGetBall(chippos,false),
	Breaker = task.goCmuRush(chippos),
	Leader   = task.multiBack(2,1),
	Middle   = task.multiBack(2,2),
	Special  = task.goCmuRush(Farpos),
	Defender = task.goCmuRush(Nearpos),
	Crosser	 = task.goCmuRush(helppos),
	Goalie   = task.goalie(),
	match    = "{A}[LM][BD][CS]"
},

["changepos"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Crosser") < 30 and player.toTargetDist("Defender") < 30,"fast") then
			return "chipball"
		elseif bufcnt(true, 225) then
			return "Shootball"
		end
	end,
	Assister = task.staticGetBall(chippos,false),
	Breaker = task.multiBack(2,1),	
	Middle   = task.multiBack(2,2),
	Special  = task.goCmuRush(getpos),	
	Defender = task.goCmuRush(Farpos),
	Crosser	 = task.goCmuRush(Nearpos),
	Leader   = task.goCmuRush(helppos),
	Goalie   = task.goalie(),
	match    = "{LMB}{A}[SD][C]"
},

["chipball"] = {
    switch = function ()
		if bufcnt(player.kickBall("Assister") , "normal") then
			return "exit"
		elseif  bufcnt(true,75) then
			return "exit"
		end
	end,
	Assister = task.chipPass(chippos,400),
	Breaker = task.goCmuRush(getpos),
	Leader   = task.multiBack(3,1),
	Special  = task.goCmuRush(Blockpos),
	Defender = task.multiBack(3,2),
	Crosser	 = task.goCmuRush(assipos),
	Middle   = task.multiBack(3,3),
	Goalie   = task.goalie(),
	match    = "{ALS}[C][DM][B]"
},

["Shootball"] = {
    switch = function ()
		if bufcnt(player.kickBall("Assister") , "normal") then
			return "exit"
		elseif  bufcnt(true,75) then
			return "exit"
		end
	end,
	Assister = task.chipPass(CGeoPoint:new_local(450,0),450),
	Breaker = task.goCmuRush(getpos),
	Leader   = task.multiBack(3,1),
	Special  = task.goCmuRush(Blockpos),
	Defender = task.multiBack(3,2),
	Crosser	 = task.goCmuRush(assipos),
	Middle   = task.multiBack(3,3),
	Goalie   = task.goalie(),
	match    = "{ALS}[C][DM][B]"
},

name = "Ref_IndirectBackKick",
applicable ={
	exp = "a",
	a   = true
},
attribute = "attack",
timeout = 99999
}
