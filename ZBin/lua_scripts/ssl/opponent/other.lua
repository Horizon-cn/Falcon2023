gOppoConfig = {
  ----------------------play---------------------------------------------------------------

	CornerKick  = {8}, -- kf
	
	FrontKick   = {41},

	MiddleKick  = {5},

	BackKick    = {"Ref_ImmortalKickV1"}, --{10, "Ref_ImmortalKickV1"}

-------------------------------Def---------------------------------------------------

	CornerDef   = "Ref_CornerDefV5", -- 可能要用v4，防头球
	BackDef 	= function()
		if math.abs(ball.refPosY()) > 100 then
			return "Ref_BackDefV10"  --保守用v5
		else
			return "Ref_BackDefV11"--挑过中场犯规脚本
		end
	end,
	MiddleDef   = "Ref_MiddleDefV10",--横向marktouch用v5，四车markfront用v10,保守打法用V2
	FrontDef    = "Ref_FrontDefV8", --四车markfront用v9,若挑就用V7，若他们四车全上就用V11,保守打法用Ref_FrontDefV2
	PenaltyKick = "Ref_PenaltyKickV1", --Ref_PenaltyKick2017V5
	PenaltyDef  = "Ref_PenaltyDefV1", --Ref_PenaltyDefV3
	KickOff		= "Ref_KickOffV6",
	KickOffDef  = "Ref_KickOffDefV1",
	NorPlay     = "NormalPlayMark"
}


--     B        -250           M        0   F_A  100  F_B  200  F_C   350
-----------------|----------------------|--------|---------|-----------|---------



--                                      0    F_D   125    F_E
----------------------------------------|-----------|----------------------------