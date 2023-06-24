if type(gOppoConfig.DirectFrontKick) == "function" then
	gCurrentPlay = cond.getOpponentScript("Ref_DirectFrontKickV", gOppoConfig.DirectFrontKick(), 11)
else
	gCurrentPlay = cond.getOpponentScript("Ref_DirectFrontKickV", gOppoConfig.DirectFrontKick, 11)
end
