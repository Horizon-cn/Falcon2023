if type(gOppoConfig.IndirectFrontKick) == "function" then
	gCurrentPlay = cond.getOpponentScript("Ref_IndirectMiddleKickV", gOppoConfig.IndirectMiddleKick(), 11)
else
	gCurrentPlay = cond.getOpponentScript("Ref_IndirectMiddleKickV", gOppoConfig.IndirectMiddleKick, 11)
end
