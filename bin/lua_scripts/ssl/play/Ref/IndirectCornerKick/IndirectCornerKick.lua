if type(gOppoConfig.IndirectCornerKick) == "function" then
	gCurrentPlay = cond.getOpponentScript("Ref_IndirectCornerKickV",gOppoConfig.IndirectCornerKick(),20)
else
	gCurrentPlay = cond.getOpponentScript("Ref_IndirectCornerKickV",gOppoConfig.IndirectCornerKick,20)
end