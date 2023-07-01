gOppoConfig = {
  ----------------------play---------------------------------------------------------------

	IndirectCornerKick  = {"Ref_IndirectCornerPush8"},--80 --"Ref_IndirectCornerPush"
	
	IndirectFrontKick   = {"Ref_IndirectFrontPush8"},--610 --"Ref_FrontPush"

	IndirectBackKick    = {"Ref_IndirectBackPush8"}, --"Ref_ImmortalKickV610" --"Ref_BackPush"  --{10, "Ref_ImmortalKickV1"}

	DirectCornerKick  = {"Ref_IndirectCornerPush8"},--80 --"Ref_IndirectCornerPush"
	
	DirectFrontKick   = {"Ref_IndirectFrontPush8"},--610 --"Ref_FrontPush"

	DirectBackKick    = {"Ref_IndirectBackPush8"}, --"Ref_ImmortalKickV610" --"Ref_BackPush"  --{10, "Ref_ImmortalKickV1"}
-------------------------------Def---------------------------------------------------

	CornerDef   = "Ref_CornerDef8", -- 可能要用v4，防头球
	BackDef 	= "Ref_BackDef8",
	MiddleDef   = "Ref_MiddleDef8",--横向marktouch用v5，四车markfront用v10,保守打法用V2
	FrontDef    = "Ref_FrontDef8", --四车markfront用v9,若挑就用V7，若他们四车全上就用V11,保守打法用Ref_FrontDefV2

	PenaltyKick = "Ref_PenaltyKick8", --Ref_PenaltyKick2017V5
	PenaltyDef  = "Ref_PenaltyDef8", --Ref_PenaltyDefV3

	KickOff		= "Ref_KickOff8",
	KickOffDef  = "Ref_KickOffDef8",
	
	NorPlay     = "NormalPlayPureDefence8"
}


--     B        -250           M        0   F_A  100  F_B  200  F_C   350
-----------------|----------------------|--------|---------|-----------|---------



--                                      0    F_D   125    F_E
----------------------------------------|-----------|----------------------------
