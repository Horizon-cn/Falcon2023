IS_TEST_MODE = true
IS_SIMULATION = CGetIsSimulation()
IS_YELLOW = CGetIsYellow()
USE_SWITCH = false
OPPONENT_NAME = "Avoidfoul" --"Avoidfoul"
USE_AUTO_REFEREE = false

gStateFileNameString = string.format(os.date("%Y%m%d%H%M"))
gTestPlay = function ()
	if not IS_YELLOW then
		return "Test_Advance" --"Test_Run"
	else
		return "Test_Advance" --"Test_PassEachOther" --"Test_NormalMiddleDefend"
	end
end --"Test_NormalDefend" --"Test_AvoidFoulDefend" 
gNormalPlay = "NormalPlayDefend"
gSwitchNum = {
	["normal"]  = 6,
	["backup"]  = 7,
	["state"]   = "normal"
}

gRoleFixNum = {
	["Kicker"]   = {5},
	["Goalie"]   = {4},
	["Tier"]	 = {3},
	["Receiver"] = {1}
}

-- 用来进行定位球的保持
-- 在考虑智能性时用table来进行配置，用于OurIndirectKick
gOurIndirectTable = {
	-- 在OurIndirectKick控制脚本中可以进行改变的值
	-- 上一次定位球的Cycle
	lastRefCycle = 0
}

gSkill = {
	--走位
	"GoAndTurn",
	"DribbleTurn",
	"GoSupport",
	--位移
	"SmartGoto",
	"GoCmuRush",
	"SimpleGoto",
	"BezierRush",
	"GotoMatchPos",
	"RunMultiPos",
	"RunMultiPosV2",
	"RunMultiPosVel",
	"GoTechChalPos",
	--踢球
	"JustKick",
	"WaitKick",
	"TouchKick",
	"ShootBall",
	"ShootBallV2",
	"GoAndTurnKick",
	"GoAndTurnKickV3",
	"GoAndTurnKickV4",
	"DribbleTurnKickV2",
	--拿球
	"GetBall",
	"SlowGetBall",
	"StaticGetBall",
	--进攻
	"ChaseKick",
	"ChaseKickV2",
	"AdvanceBall",
	"AdvanceBallV3",
	"AdvanceBallV4",
	--防守
	"Marking",
	"MarkingTouch",
	"Goalie2013",
	"Goalie2022",
	"ProtectBall",
	--传球
	"ReceivePass",
	--展示
	"GoAroundBall",
	"GoAroundRobot",
	"GoPIDCircle",
	--放球
	"FetchBall",
	--停止
	"Stop",
	--点球
	"PenaltyKick",
	"PenaltyGoalie",
	"Break",
	"PenaltyKickV2",
	--测试
	"TimeDelayTest",

}

gRefPlayTable = {
	--开球进攻
	"Ref/KickOff/Ref_KickOffV6",

	--角球进攻
	"Ref/CornerKick/Ref_CornerKickV1",
	"Ref/CornerKick/Ref_CornerKickV8",
	"Ref/CornerKick/Ref_CornerKickV30",
	"Ref/CornerKick/Ref_CornerKickV201",
	"Ref/CornerKick/Ref_CornerKickV202",
	"Ref/CornerKick/Ref_CornerKickV300",
	"Ref/CornerKick/Ref_CornerKickV2",
	--前场进攻
	"Ref/FrontKick/Ref_FrontKickV23",
	"Ref/FrontKick/Ref_FrontKickV41",
	"Ref/FrontKick/Ref_FrontKickV2",

	--中场进攻
	"Ref/MiddleKick/Ref_MiddleKickV1",
	"Ref/MiddleKick/Ref_MiddleKickV5",
	"Ref/MiddleKick/Ref_MiddleKickV2",

	--后场进攻
	"Ref/BackKick/Ref_BackKickV1",
	"Ref/BackKick/Ref_ImmortalKickV1",
	"Ref/BackKick/Ref_BackKickV2",
	
	--开球防守
	"Ref/KickOffDef/Ref_KickOffDefV1",

	--角球防守
	"Ref/CornerDef/Ref_CornerDefV5",
	"Ref/CornerDef/Ref_CornerDefV2",

	--中场防守
	"Ref/MiddleDef/Ref_MiddleDefV10",
	"Ref/MiddleDef/Ref_MiddleDefV11",
	"Ref/MiddleDef/Ref_MiddleDefV2",

	--前场防守
	"Ref/FrontDef/Ref_FrontDefV8",
	"Ref/FrontDef/Ref_FrontDefV9",
	"Ref/FrontDef/Ref_FrontDefV2",

	--后场防守
	"Ref/BackDef/Ref_BackDefV10",
	"Ref/BackDef/Ref_BackDefV11",
	"Ref/BackDef/Ref_BackDefV12",
	"Ref/BackDef/Ref_BackDefV2",

	--己方放球
	"Ref/BallPlace/Ref_OurBallPlaceV2",

	--对方放球
	"Ref/BallPlace/Ref_TheirBallPlace",

	--点球进攻
	"Ref/PenaltyKick/Ref_PenaltyKickV1",

	--点球防守
	"Ref/PenaltyDef/Ref_PenaltyDefV1",

	--停止站位
	"Ref/GameStop/Ref_Stop4BackKick",
	"Ref/GameStop/Ref_StopV2",
	"Ref/GameStop/Ref_StopV3",
	"Ref/GameStop/Ref_Stop4CornerDef",
	"Ref/GameStop/Ref_Stop4CornerKick",
	"Ref/GameStop/Ref_Stop4SideLine",
	"Ref/GameStop/Ref_Stop4FrontKick",
	"Ref/GameStop/Ref_Stop4MiddleKick",
	"Ref/GameStop/Ref_Stop4ChaKick",


	--强制停止
	"Ref/Ref_HaltV1",
}

gBayesPlayTable = {
	"Nor/NormalPlayMark",
}

gTestPlayTable = {

	"Test_Run",
	"Test_BezierRun",
	"Test_GetBall",
	"Test_ChaseKick",
	"Test_PassNormal",
	"Test_ReceivePass",
	"Test_PassEachOther",
	
	"Test_Advance",
	"Test_GoSupport",
	"Test_AdvanceV4",
	"Test_TouchKick",
	"Test_Defence",
	"Test_Goalie",
	"Test_MultiBack",
	"Test_ProtectBall",
	"Test_TimeDelayTest",
	"Test_GoTechChalPos",
	"Test_NormalPlay",
	"Test_NormalAttack",
	"Test_NormalDefend",
	"Test_AvoidFoulDefend",
	"Test_NormalMiddleDefend",
	"Test_Circle"
}
