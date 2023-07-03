if type(gOppoConfig.DirectCornerKick) == "function" then
	gCurrentPlay = cond.getOpponentScript("Ref_DirectCornerKickV",gOppoConfig.DirectCornerKick(),20)
else
	gCurrentPlay = cond.getOpponentScript("Ref_DirectCornerKickV",gOppoConfig.DirectCornerKick,20)
end