module(..., package.seeall)

IS_SIMULATION = CGetIsSimulation()
IS_YELLOW = CGetIsYellow()

maxPlayer   = CGetFieldParam("MAX_PLAYER") -- 8
pitchLength = CGetFieldParam("PITCH_LENGTH") -- 1200
pitchWidth  = CGetFieldParam("PITCH_WIDTH") -- 900
goalWidth = CGetFieldParam("GOAL_WIDTH") -- 120
goalDepth = CGetFieldParam("GOAL_DEPTH") -- 20
freeKickAvoidBallDist = CGetFieldParam("FREE_KICK_AVOID_BALL_DIST") -- 55
playerRadius	= CGetFieldParam("PLAYER_SIZE") -- 9
penaltyWidth    = CGetFieldParam("PENALTY_AREA_WIDTH") -- 240	-- 195
penaltyDepth	= CGetFieldParam("PENALTY_AREA_DEPTH") -- 120	-- 85
penaltyRadius	= CGetFieldParam("PENALTY_AREA_R") -- 85	-- 85
penaltySegment	= CGetFieldParam("PENALTY_AREA_L") -- 35	--
playerFrontToCenter = CGetFieldParam("PLAYER_FRONT_TO_CENTER") -- 7.6
lengthRatio	= 1
widthRatio	= 1
