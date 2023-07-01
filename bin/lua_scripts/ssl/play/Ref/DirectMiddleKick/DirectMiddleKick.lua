if type(gOppoConfig.DirectFrontKick) == "function" then
	gCurrentPlay = cond.getOpponentScript("Ref_DirectMiddleKickV", gOppoConfig.DirectMiddleKick(), 11)
else
	gCurrentPlay = cond.getOpponentScript("Ref_DirectMiddleKickV", gOppoConfig.DirectMiddleKick, 11)
end
