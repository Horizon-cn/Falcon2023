local chipPower = 300
local TAR_POS = (CGeoPoint:new_local(400, 0))
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
		if bufcnt(player.InfoControlled("Assister") and player.toTargetDist(role) < 30, 10, 120) then
			return "chipball"
		end
		
	end,
	Assister = task.staticGetBall(TAR_POS),
	Special  = task.goCmuRush(TAR_POS,_,_,flag.allow_dss),
	Engine   = task.goMWPassPos("Assister"),
	Hawk     = task.marking("First"),
	Leader   = task.goCmuRush(FREEKICKPOS,_,_,flag.allow_dss),
	Defender  = task.rightBack(),--task.defendMiddle4Stop(),--TODO
	Middle   = task.leftBack(),
	Goalie   = task.goalieNew(),
	match    = "{A}{DM}{S}[LEH]"
},	

["chipball"] = {
    switch = function ()
		print("chip")
		if bufcnt(player.kickBall("Assister") or
				  player.toBallDist("Assister") > 20, 3, 120) then
			return "waitball"
		elseif  bufcnt(true,60) then
			return "exit"
		end
	end,
	Assister = task.chipPass(TAR_POS, chipPower),
	Special  = task.goCmuRush(TAR_POS,_,_,flag.allow_dss),
	Engine   = task.goMWPassPos("Assister"),
	Hawk     = task.marking("First"),
	Leader   = task.goCmuRush(ball.refAntiYPos(ball.pos()),_,_,flag.allow_dss),
	Defender  = task.rightBack(),--task.defendMiddle4Stop(),--TODO
	Middle   = task.leftBack(),
	Goalie   = task.goalieNew(),
	match    = "{A}{DM}{S}{LEH}"
},

["waitball"] = {
    switch = function ()
		if bufcnt(false, 1, 180) then
			return "exit"
		end
	end,
	Assister = task.stop(),
	Special  = task.advance(),
	Engine   = task.goMWPassPos("Assister"),
	Hawk     = task.marking("First"),
	Leader   = task.goCmuRush(ball.refAntiYPos(ball.pos()),_,_,flag.allow_dss),
	Defender  = task.rightBack(),--task.defendMiddle4Stop(),--TODO
	Middle   = task.leftBack(),
	Goalie   = task.goalieNew(),
	match    = "{S}{DM}{L}{EHA}"
},

name = "Ref_MiddleKickV5",
applicable ={
	exp = "a",
	a   = true
},
attribute = "attack",
timeout = 99999
}
