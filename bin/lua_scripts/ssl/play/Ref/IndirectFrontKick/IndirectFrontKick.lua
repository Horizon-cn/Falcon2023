if type(gOppoConfig.IndirectFrontKick) == "function" then
	gCurrentPlay = cond.getOpponentScript("Ref_IndirectFrontKickV", gOppoConfig.IndirectFrontKick(), 11)
else
	gCurrentPlay = cond.getOpponentScript("Ref_IndirectFrontKickV", gOppoConfig.IndirectFrontKick, 11)
end
