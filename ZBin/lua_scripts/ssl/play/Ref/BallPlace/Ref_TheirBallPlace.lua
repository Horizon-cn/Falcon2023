local COR_DEF_POS1 = CGeoPoint:new_local(-50*param.lengthRatio,-50*param.widthRatio)
local SIDE_POS, MIDDLE_POS, INTER_POS = pos.refStopAroundBall()

local BALL_PLACE_FLAG = flag.dodge_ball+flag.allow_dss+flag.their_baLL_placement

local PENALTY_THRESHOLD_DIST = 420
local MIDDLE_THRESHOLD_Y = 0.125 * param.pitchWidth --75

local topX = -(param.pitchLength/2 - param.penaltyDepth - 2 * param.playerRadius)
local sideY = param.penaltyWidth/2 + 2 * param.playerRadius
local rightTop = {
  CGeoPoint:new_local(topX, 0),
  CGeoPoint:new_local(topX, 20),
  CGeoPoint:new_local(topX, 40),
  CGeoPoint:new_local(topX, 60),
  CGeoPoint:new_local(topX, 80),
  CGeoPoint:new_local(topX, 100)
}
local leftTop = {
  CGeoPoint:new_local(topX, -0),
  CGeoPoint:new_local(topX, -20),
  CGeoPoint:new_local(topX, -40),
  CGeoPoint:new_local(topX, -60),
  CGeoPoint:new_local(topX, -80),
  CGeoPoint:new_local(topX, -100)
}
local side = {
  CGeoPoint:new_local(topX - 0, sideY),
  CGeoPoint:new_local(topX - 0, -sideY),
  CGeoPoint:new_local(topX - 20, sideY),
  CGeoPoint:new_local(topX - 20, -sideY),
  CGeoPoint:new_local(topX - 40, sideY),
  CGeoPoint:new_local(topX - 40, -sideY)
}
local leftSide = {
  CGeoPoint:new_local(topX - 0, -sideY),
  CGeoPoint:new_local(topX - 20, -sideY),
  CGeoPoint:new_local(topX - 40, -sideY),
  CGeoPoint:new_local(topX - 60, -sideY),
  CGeoPoint:new_local(topX - 80, -sideY),
  CGeoPoint:new_local(topX - 100, -sideY)
}

local PointA = CGeoPoint:new_local(-300, -160)
local PointB = CGeoPoint:new_local(-300, 160)
local PointC = CGeoPoint:new_local(-200, 0)

local standPos = leftTop
local standFunc = function(num)
  return function()
    return standPos[num]
  end
end

gPlayTable.CreatePlay{

firstState = "beginning",

switch = function()	
	if ball.posX() > topX then --top
      standPos = side
    elseif ball.posX() < topX and ball.posY() > 0 then--right side
      standPos = leftTop
    else --ballPosX() < topX and ballPosY() < 0 then--left side
      standPos = rightTop
    end

	if gCurrentState == "beginning" and 
		enemy.attackNum() <= 8 and enemy.attackNum() > 0 then
		return "attacker"..enemy.attackNum()
	else
		if cond.isGameOn() and cond.OurBallPlace() then
			return "exit"
		elseif enemy.situChanged() and
			enemy.attackNum() <= 8 and enemy.attackNum() > 0 then
			return "attacker"..enemy.attackNum()
		end
	end
end,

-- headback sideback defend middle
["beginning"] = {
    -- Assister = task.goCmuRush(standFunc(1), dir.playerToBall, ACC, BALL_PLACE_FLAG),
    -- Special  = task.goCmuRush(standFunc(2), dir.playerToBall, ACC, BALL_PLACE_FLAG),
    -- Leader   = task.goCmuRush(standFunc(3), dir.playerToBall, ACC, BALL_PLACE_FLAG),
  Assister = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Leader   = task.goCmuRush(PointC, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Defender = task.leftBack(),
    Middle   = task.rightBack(),
    -- Fronter  = task.goCmuRush(standFunc(6), dir.playerToBall, ACC, STOP_DSS),
    -- Center   = task.stop(),--task.goCmuRush(SEVEN_POS, dir.playerToBall, ACC, STOP_DSS),
    Goalie   = task.goalie(),
    match    = "[AMDLS]"
},

["attacker1"] = {
	Assister = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Leader   = task.goCmuRush(PointC, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Defender = task.leftBack(),
    Middle   = task.rightBack(),
    -- Fronter  = task.goCmuRush(standFunc(6), dir.playerToBall, ACC, STOP_DSS),
    -- Center   = task.stop(),--task.goCmuRush(SEVEN_POS, dir.playerToBall, ACC, STOP_DSS),
    Goalie   = task.goalie(),
    match    = "[AMDLS]"
},

["attacker2"] = {
  Assister = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Leader   = task.goCmuRush(PointC, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Defender = task.leftBack(),
    Middle   = task.rightBack(),
    -- Fronter  = task.goCmuRush(standFunc(6), dir.playerToBall, ACC, STOP_DSS),
    -- Center   = task.stop(),--task.goCmuRush(SEVEN_POS, dir.playerToBall, ACC, STOP_DSS),
    Goalie   = task.goalie(),
    match    = "[AMDLS]"
},

["attacker3"] = {
  Assister = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Leader   = task.goCmuRush(PointC, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Defender = task.leftBack(),
    Middle   = task.rightBack(),
    -- Fronter  = task.goCmuRush(standFunc(6), dir.playerToBall, ACC, STOP_DSS),
    -- Center   = task.stop(),--task.goCmuRush(SEVEN_POS, dir.playerToBall, ACC, STOP_DSS),
    Goalie   = task.goalie(),
    match    = "[AMDLS]"
},

["attacker4"] = {
  Assister = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Leader   = task.goCmuRush(PointC, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Defender = task.leftBack(),
    Middle   = task.rightBack(),
    -- Fronter  = task.goCmuRush(standFunc(6), dir.playerToBall, ACC, STOP_DSS),
    -- Center   = task.stop(),--task.goCmuRush(SEVEN_POS, dir.playerToBall, ACC, STOP_DSS),
    Goalie   = task.goalie(),
    match    = "[AMDLS]"
},

["attacker5"] = {
  Assister = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Leader   = task.goCmuRush(PointC, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Defender = task.leftBack(),
    Middle   = task.rightBack(),
    -- Fronter  = task.goCmuRush(standFunc(6), dir.playerToBall, ACC, STOP_DSS),
    -- Center   = task.stop(),--task.goCmuRush(SEVEN_POS, dir.playerToBall, ACC, STOP_DSS),
    Goalie   = task.goalie(),
    match    = "[AMDLS]"
},

["attacker6"] = {
  Assister = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Leader   = task.goCmuRush(PointC, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Defender = task.leftBack(),
    Middle   = task.rightBack(),
    -- Fronter  = task.goCmuRush(standFunc(6), dir.playerToBall, ACC, STOP_DSS),
    -- Center   = task.stop(),--task.goCmuRush(SEVEN_POS, dir.playerToBall, ACC, STOP_DSS),
    Goalie   = task.goalie(),
    match    = "[AMDLS]"
},

["attacker7"] = {
  Assister = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Leader   = task.goCmuRush(PointC, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Defender = task.leftBack(),
    Middle   = task.rightBack(),
    -- Fronter  = task.goCmuRush(standFunc(6), dir.playerToBall, ACC, STOP_DSS),
    -- Center   = task.stop(),--task.goCmuRush(SEVEN_POS, dir.playerToBall, ACC, STOP_DSS),
    Goalie   = task.goalie(),
    match    = "[AMDLS]"
},

["attacker8"] = {
  Assister = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Leader   = task.goCmuRush(PointC, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Defender = task.leftBack(),
    Middle   = task.rightBack(),
    -- Fronter  = task.goCmuRush(standFunc(6), dir.playerToBall, ACC, STOP_DSS),
    -- Center   = task.stop(),--task.goCmuRush(SEVEN_POS, dir.playerToBall, ACC, STOP_DSS),
    Goalie   = task.goalie(),
    match    = "[AMDLS]"
},

name = "Ref_TheirBallPlace",
applicable ={
	exp = "a",
	a   = true
},
attribute = "defense",
timeout   = 99999
}