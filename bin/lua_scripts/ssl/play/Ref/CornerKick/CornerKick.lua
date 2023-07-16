if type(gOppoConfig.CornerKick) == "function" then
	gCurrentPlay = cond.getOpponentScript("Ref_CornerKickV",gOppoConfig.CornerKick(),20)
else
	gCurrentPlay = cond.getOpponentScript("Ref_CornerKickV",gOppoConfig.CornerKick,20)
end