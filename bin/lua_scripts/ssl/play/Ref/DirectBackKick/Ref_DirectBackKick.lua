local FreeKick_ImmortalStart_Pos = function ()
	local pos
	local ball2goal = CVector:new_local(CGeoPoint:new_local(450, 0) - ball.pos())
	pos = ball.pos() + Utils.Polar2Vector(80, ball2goal:dir())
	local tempPos = ball.pos()+ Utils.Polar2Vector(80, ball2goal:dir())
	for i = 1, 6 do
		if vision:TheirPlayer(i):Valid() then
			if vision:TheirPlayer(i):Pos():dist(tempPos) < 20 then
				local dir = (CGeoPoint:new_local(450, 30 * ball.antiY()) - vision:TheirPlayer(i):Pos()):dir()
				pos = vision:TheirPlayer(i):Pos() + Utils.Polar2Vector(20, dir)
				break
			end
		else
			pos = tempPos
		end
		
	end
	return pos
end

local Field_RobotFoward_Pos = function (role)
	local pos
	local UpdatePos = function ()
		local roleNum = player.num(role)
		if Utils.PlayerNumValid(roleNum) then
			local carPos = vision:OurPlayer(roleNum):Pos()
			pos = carPos + Utils.Polar2Vector(1, vision:OurPlayer(roleNum):Dir())
		end
		return pos
	end
	return UpdatePos
end
local Blockpos = ball.refAntiYPos(CGeoPoint:new_local(435,70))
local Farpos = ball.refAntiYPos(CGeoPoint:new_local(-130,275))
local Nearpos = ball.refAntiYPos(CGeoPoint:new_local(-60,110))
local Shootingpos = ball.refAntiYPos(CGeoPoint:new_local(500,212))
local FREEKICKPOS
local FIELDROBOTPOS
FREEKICKPOS = FreeKick_ImmortalStart_Pos

PreGoPos = function (role)
	return function ()
		return player.pos(role) + Utils.Polar2Vector(5, player.dir(role))
	end
end

gPlayTable.CreatePlay{

firstState = "startball",

["startball"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Breaker") < 30, "fast") then
			return "changepos"
		elseif bufcnt(true, 300) then
			return "exit"
		end
	end,
	Assister = task.staticGetBall(ball.refAntiYPos(CGeoPoint:new_local(0, -300))),
	Breaker = task.goCmuRush(ball.refAntiYPos(CGeoPoint:new_local(0,-300))),
	Leader   = task.rightBack(),
	Middle   = task.leftBack(),
	Special  = task.goCmuRush(Farpos),
	Defender = task.goCmuRush(Nearpos),
	Crosser	 = task.goCmuRush(ball.refAntiYPos(CGeoPoint:new_local(-270,-390))),
	Goalie   = task.goalie(),
	match    = "{A}[LM][BD][CS]"
},

["changepos"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Crosser") < 30 and player.toTargetDist("Defender") < 30,"fast") then
			return "chipball"
		elseif bufcnt(true, 225) then
			return "exit"
		end
	end,
	Assister = task.staticGetBall(ball.refAntiYPos(CGeoPoint:new_local(0, -300))),
	Breaker = task.leftBack(),	
	Middle   = task.rightBack(),
	Special  = task.goCmuRush(ball.refAntiYPos(CGeoPoint:new_local(0,-300))),	
	Defender = task.goCmuRush(Farpos),
	Crosser	 = task.goCmuRush(Nearpos),
	Leader   = task.goCmuRush(ball.refAntiYPos(CGeoPoint:new_local(-270,-390))),
	Goalie   = task.goalie(),
	match    = "{LMB}{A}[SD][C]"
},

["chipball"] = {
    switch = function ()
		if bufcnt(player.kickBall("Assister") or
				  player.toBallDist("Assister") > 20, "fast") then
			return "exit"
		elseif  bufcnt(true,75) then
			return "exit"
		end
	end,
	Assister = task.chipPass(ball.refAntiYPos(CGeoPoint:new_local(0,-300)),500),
	Breaker = task.goCmuRush(ball.refAntiYPos(CGeoPoint:new_local(0,-300))),
	Leader   = task.singleBack(),
	Special  = task.goCmuRush(Blockpos),
	Defender = task.leftBack(),
	Crosser	 = task.goCmuRush(Nearpos),
	Middle   = task.rightBack(),
	Goalie   = task.goalie(),
	match    = "{ALS}[C][DM][B]"
},



name = "Ref_DirectBackKick",
applicable ={
	exp = "a",
	a   = true
},
attribute = "attack",
timeout = 99999
}
