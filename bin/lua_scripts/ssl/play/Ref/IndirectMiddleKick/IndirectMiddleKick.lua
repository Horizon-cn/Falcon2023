if type(gOppoConfig.IndirectMiddleKick) == "function" then
	gCurrentPlay = cond.getOpponentScript("Ref_IndirectMiddleKick_normal_middle", gOppoConfig.IndirectMiddleKick(), 4)
else
	gCurrentPlay = cond.getOpponentScript("Ref_MiddleKickV", gOppoConfig.MiddleKick, 4)
end
