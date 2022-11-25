local function def_chipPower()
	return 450
end


local TAR_POS = CGeoPoint:new_local(-100, 0)
local FreeKick_ImmortalStart_Pos = function ()
	local pos
	local ball2goal = CVector:new_local(CGeoPoint:new_local(600, 0) - ball.pos())
	pos = ball.pos() + Utils.Polar2Vector(200, ball2goal:dir())
	local tempPos = ball.pos()+ Utils.Polar2Vector(200, ball2goal:dir())
	for i = 1, 6 do
		if vision:TheirPlayer(i):Valid() then
			if vision:TheirPlayer(i):Pos():dist(tempPos) < 20 then
				local dir = (CGeoPoint:new_local(600, 30 * ball.antiY()) - vision:TheirPlayer(i):Pos()):dir()
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

local FREEKICKPOS
local FIELDROBOTPOS
FREEKICKPOS = FreeKick_ImmortalStart_Pos

PreGoPos = function (role)
	return function ()
		return player.pos(role) + Utils.Polar2Vector(5, player.dir(role))
	end
end

Role2Pass = function (role1, role2, role3, role4, role5)
	if player.canChipPassTo(role1, role2) then
		return role2
	elseif player.canChipPassTo(role1, role3) then
		return role3
	elseif player.canChipPassTo(role1, role4) then
		return role4
	else
		return role5
	end
end
gPlayTable.CreatePlay{

firstState = "getball",

["getball"] = {
	switch = function ()
		local role = Role2Pass("Assister", "Special", "Engine", "Hawk", "Leader")
		if bufcnt(player.InfoControlled("Assister") and player.toTargetDist(role) < 30, 10) then
			return "chipball"
		end
		
	end,
	--Assister = task.staticGetBall(ball.LMPassPos()),
	Assister = task.staticGetBall(TAR_POS),
	--Special  = task.goLMPassPos("Assister"),
	Special  = task.goCmuRush(TAR_POS, _, ACC, STOP_DSS),
	Engine   = task.goLeftSupport(),
	Hawk     = task.goRightSupport(),
	Leader   = task.goRWPassPos("Assister"),
	Defender  = task.rightBack(),--task.defendMiddle4Stop(),--TODO
	Middle   = task.leftBack(),
	Goalie   = task.goalieNew(),
	match    = "{DM}{AS}[LEH]"
},	

["chipball"] = {
    switch = function ()

		if bufcnt(player.kickBall("Assister") or
				  player.toBallDist("Assister") > 20 and false, 3) then
			return "waitball"
		elseif  bufcnt(false,180) then
			print("why here?")
			return "exit"
		end
	end,
	--Assister = task.chipPass(ball.LMPassPos(), chipPower, false),
	Assister = task.chipPass(TAR_POS, def_chipPower()),
	--Special  = task.goLMPassPos("Assister"),
	Special  = task.goCmuRush(TAR_POS, _, ACC, STOP_DSS),
	Engine   = task.goLeftSupport(),
	Hawk     = task.goRightSupport(),
	Leader   = task.goCmuRush(ball.refAntiYPos(ball.pos()), _, ACC, STOP_DSS),
	Defender  = task.rightBack(),--task.defendMiddle4Stop(),--TODO
	Middle   = task.leftBack(),
	Goalie   = task.goalieNew(),
	match    = "{DM}{AS}{LEH}"
},

["waitball"] = {
    switch = function ()
		print("wait")
		if bufcnt(false, 1, 180) then
			return "exit"
		end
	end,
	Assister = task.stop(),
	Special  = task.advance(),
	Engine   = task.goLeftSupport(),
	Hawk     = task.goRightSupport(),
	Leader   = task.goCmuRush(ball.refAntiYPos(ball.pos()),  _, ACC, STOP_DSS),
	Defender  = task.rightBack(),--task.defendMiddle4Stop(),--TODO
	Middle   = task.leftBack(),
	Goalie   = task.goalieNew(),
	match    = "{DM}{AS}{LEH}"
},

name = "Ref_ImmortalKickV1",
applicable ={
	exp = "a",
	a   = true
},
attribute = "attack",
timeout = 99999
}
