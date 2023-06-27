IS_TEST_MODE = true
IS_SIMULATION = CGetIsSimulation()
IS_YELLOW = CGetIsYellow()
USE_SWITCH = false
OPPONENT_NAME = "other"--"Avoidfoul" PureDefence6 PureDefence8 NormalKick
USE_AUTO_REFEREE = false

gStateFileNameString = string.format(os.date("%Y%m%d%H%M"))
gTestPlay = function ()
	if not IS_YELLOW then
		return "Test_AdvanceV4" --"Test_AdvanceV4"  --"NormalPlayPureDefence" --"Test_Run6" --"Test_play6" --"Test_Run"
		-- Test_Run6 测testrun
		-- Test_play6ForTest测三车进攻
	else
		return "Test_AdvanceV4" --"Test_Defence" --"Test_PassEachOther" --"Test_NormalMiddleDefend"
	end
end --"Test_NormalDefend" --"Test_AvoidFoulDefend" 
gNormalPlay = "NormalPlayDefend"
gSwitchNum = {
	["normal"]  = 6,
	["backup"]  = 7,
	["state"]   = "normal"
}

-- 有0号在场门将就是0号，没有0号在场，看这里设置的号码
-- 建议比赛时只要上了0号，这里就写0号，否则万一0号视觉丢了，就会匹配其他车去当门将，犯规
gRoleFixNum = {
	["Kicker"]   = {15},
	["Goalie"]   = {11},
	["Tier"]	 = {13},
	["Receiver"] = {12}
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
	"SpeedTest",
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
	"Ref/KickOff/Ref_KickOffV23",
	"Ref/KickOff/Ref_KickOffV230",
	"Ref/KickOff/Ref_KickOff8",
	"Ref/KickOff/Ref_KickOff_normal",


	--角球进攻
	"Ref/CornerKick/Ref_CornerKickV1",
	"Ref/CornerKick/Ref_CornerKickV6",
	"Ref/CornerKick/Ref_CornerKickV8",
	"Ref/CornerKick/Ref_CornerKickV80",
	"Ref/CornerKick/Ref_CornerKickV30",
	"Ref/CornerKick/Ref_CornerKickV201",
	"Ref/CornerKick/Ref_CornerKickV202",
	"Ref/CornerKick/Ref_CornerKickV300",
	"Ref/CornerKick/Ref_CornerKickV2",
	"Ref/CornerKick/Ref_CornerPush",
	"Ref/CornerKick/Ref_CornerPush8",
	"Ref/CornerKick/Ref_CornerPush_normal",
	--前场进攻
	"Ref/FrontKick/Ref_FrontKickV23",
	"Ref/FrontKick/Ref_FrontKickV41",
	"Ref/FrontKick/Ref_FrontKickV2",
	"Ref/FrontKick/Ref_FrontKickV61",
	"Ref/FrontKick/Ref_FrontKickV610",
	"Ref/FrontKick/Ref_FrontPush",
	"Ref/FrontKick/Ref_FrontPush8",
	"Ref/FrontKick/Ref_FrontPush_normal",

	--中场进攻
	"Ref/MiddleKick/Ref_MiddleKickV1",
	"Ref/MiddleKick/Ref_MiddleKickV5",
	"Ref/MiddleKick/Ref_MiddleKickV2",

	--后场进攻
	"Ref/BackKick/Ref_BackKickV1",
	"Ref/BackKick/Ref_ImmortalKickV1",
	"Ref/BackKick/Ref_BackKickV2",
	"Ref/BackKick/Ref_ImmortalKickV61",
	"Ref/BackKick/Ref_ImmortalKickV610",
	"Ref/BackKick/Ref_BackPush",
	"Ref/BackKick/Ref_BackPush8",
	"Ref/BackKick/Ref_BackPush_normal",
	
	--开球防守
	"Ref/KickOffDef/Ref_KickOffDefV1",
	"Ref/KickOffDef/Ref_KickOffDefV23",
	"Ref/KickOffDef/Ref_KickOffDefV230",
	"Ref/KickOffDef/Ref_KickOffDef8",
	"Ref/KickOffDef/Ref_KickOffDef_normal",

	--角球防守
	"Ref/CornerDef/Ref_CornerDefV5",
	"Ref/CornerDef/Ref_CornerDefV2",
	"Ref/CornerDef/Ref_CornerDefV20",
	"Ref/CornerDef/Ref_CornerDef8",
	"Ref/CornerDef/Ref_CornerDef_normal",

	--中场防守
	"Ref/MiddleDef/Ref_MiddleDefV10",
	"Ref/MiddleDef/Ref_MiddleDefV11",
	"Ref/MiddleDef/Ref_MiddleDefV2",
	"Ref/MiddleDef/Ref_MiddleDefV20",
	"Ref/MiddleDef/Ref_MiddleDef8",
	"Ref/MiddleDef/Ref_MiddleDef_normal",

	--前场防守
	"Ref/FrontDef/Ref_FrontDefV8",
	"Ref/FrontDef/Ref_FrontDefV9",
	"Ref/FrontDef/Ref_FrontDefV2",
	"Ref/FrontDef/Ref_FrontDefV20",
	"Ref/FrontDef/Ref_FrontDef8",
	"Ref/FrontDef/Ref_FrontDef_normal",

	--后场防守
	"Ref/BackDef/Ref_BackDefV10",
	"Ref/BackDef/Ref_BackDefV11",
	"Ref/BackDef/Ref_BackDefV12",
	"Ref/BackDef/Ref_BackDefV2",
	"Ref/BackDef/Ref_BackDefV20",
	"Ref/BackDef/Ref_BackDef8",
	"Ref/BackDef/Ref_BackDef_normal",

	--己方放球
	"Ref/BallPlace/Ref_OurBallPlaceV2",

	--对方放球
	"Ref/BallPlace/Ref_TheirBallPlace",

	--点球进攻
	"Ref/PenaltyKick/Ref_PenaltyKickV1",
	"Ref/PenaltyKick/Ref_PenaltyKickV6",
	"Ref/PenaltyKick/Ref_PenaltyKickV60",
	"Ref/PenaltyKick/Ref_PenaltyKick8",
	"Ref/PenaltyKick/Ref_PenaltyKick_normal",

	--点球防守
	"Ref/PenaltyDef/Ref_PenaltyDefV1",
	"Ref/PenaltyDef/Ref_PenaltyDefV6",
	"Ref/PenaltyDef/Ref_PenaltyDefV60",
	"Ref/PenaltyDef/Ref_PenaltyDef8",
	"Ref/PenaltyDef/Ref_PenaltyDef_normal",

	--停止站位
	"Ref/GameStop/Ref_Stop4BackKick",
	"Ref/GameStop/Ref_StopV2",
	"Ref/GameStop/Ref_StopV3",
	"Ref/GameStop/Ref_Stop4CornerDef",
	"Ref/GameStop/Ref_Stop4CornerKick",
	"Ref/GameStop/Ref_Stop4CornerKick6",
	"Ref/GameStop/Ref_Stop4SideLine",
	"Ref/GameStop/Ref_Stop4FrontKick",
	"Ref/GameStop/Ref_Stop4MiddleKick",
	"Ref/GameStop/Ref_Stop4ChaKick",

	"Ref/GameStop/Ref0_StopV2",
	"Ref/GameStop/Ref0_StopV3",
	"Ref/GameStop/Ref0_Stop4CornerDef",
	"Ref/GameStop/Ref0_Stop4CornerKick",

	
	"Ref/GameStop/Ref_StopV2V8",
	"Ref/GameStop/Ref_StopV3V8",
	"Ref/GameStop/Ref_Stop4CornerDefV8",
	"Ref/GameStop/Ref_Stop4CornerKickV8",

	"Ref/GameStop/Ref1_StopV2",
	"Ref/GameStop/Ref1_StopV3",
	"Ref/GameStop/Ref1_Stop4CornerDef",
	"Ref/GameStop/Ref1_Stop4CornerKick",

	"Ref/GameStop/Ref_StopV2_normal",
	"Ref/GameStop/Ref_StopV3_normal",
	"Ref/GameStop/Ref_Stop4CornerDef_normal",
	"Ref/GameStop/Ref_Stop4CornerKick_normal",


	"Ref/GameStop/Ref_StopBack",


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
	"Test_StaticGetBall",
	"Test_Speed",
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
	"Test_Circle",
	"Test_play6",
	"NormalPlay",
	"NormalPlayPureDefence",
	"NormalPlayPureDefence8",
	"Test_defend6",
	"Test_play6ForTest",
	"Test_DSS",
	"Test_Run6",
	"Test_play3",
	"Test_NormalPass"
}
