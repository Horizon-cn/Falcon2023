-- test modify
local isUsePass = false
local FAKE_DEFEND_POS = ball.antiYPos(CGeoPoint:new_local(250,50))


gPlayTable.CreatePlay{
firstState = "initState",

["initState"] = {
	switch = function ()
		-- return gCurrentFieldArea..gCurrentBallStatus.."L"
		return "initState"
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][BC][AD][M][S]"
},


["FrontFieldNoneL"]={
	switch=function ()
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()<=0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."NormR"
		end
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()>0,20) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][AD][M][S]"
},
["FrontFieldNoneR"]={
	switch=function ()
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()<=0,20) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()>0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][AD][M][S]"
},



["FrontFieldStandOffL"]={
	switch=function ()
		if cond.bestPlayerChanged() or gCurrentBallStatus ~= "StandOff" and bufcnt(ball.posY()<=0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if cond.bestPlayerChanged() or gCurrentBallStatus ~= "StandOff" and bufcnt(ball.posY()>0,20) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][AD][M][S]"
},
["FrontFieldStandOffR"]={
	switch=function ()
		if cond.bestPlayerChanged() or gCurrentBallStatus ~= "StandOff" and bufcnt(ball.posY()<=0,20) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if cond.bestPlayerChanged() or gCurrentBallStatus ~= "StandOff" and bufcnt(ball.posY()>0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][AD][M][S]"
},



["FrontFieldOurBallL"]={
	switch=function ()
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()<=0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()>0,20) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][AD][S][M]"

},
["FrontFieldOurBallR"]={
	switch=function ()
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()<=0,20) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()>0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][AD][S][M]"

},


["BackFieldNoneL"]={
	switch=function ()
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()<=0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()>0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][DA][S][M]"
},

["BackFieldNoneR"]={
	switch=function ()
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()<=0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()>0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][AD][S][M]"
},



["BackFieldStandOffL"]={
	switch=function ()
		if cond.bestPlayerChanged() or gCurrentBallStatus ~= "StandOff" and bufcnt(ball.posY()<=0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if cond.bestPlayerChanged() or gCurrentBallStatus ~= "StandOff" and bufcnt(ball.posY()>0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][D][A][M][S]"
},

["BackFieldStandOffR"]={
	switch=function ()
		if cond.bestPlayerChanged() or gCurrentBallStatus ~= "StandOff" and bufcnt(ball.posY()<=0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if cond.bestPlayerChanged() or gCurrentBallStatus ~= "StandOff" and bufcnt(ball.posY()>0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][A][D][M][S]"
},


["BackFieldOurBallL"]={
	switch=function ()
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()<=0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()>0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][DA][S][M]"

},
["BackFieldOurBallR"]={
	switch=function ()
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()<=0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."R"
		end
		if gCurrentFieldArea..gCurrentBallStatus ~= gLastState and bufcnt(ball.posY()>0,5) then
			return gCurrentFieldArea..gCurrentBallStatus.."L"
		end
	end,
	Leader = task.advanceV4(),
	Special = task.goRightSupport(),
	Middle = task.goLeftSupport(),
	Defender = task.leftBack(),
	Assister = task.rightBack(),
	Goalie   = task.goalieNew(),
	match    = "[L][AD][S][M]"

},

name = "NormalPlayMark",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}