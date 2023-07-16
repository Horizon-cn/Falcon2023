if type(gOppoConfig.KickOff) == "function" then
	gCurrentPlay = cond.getOpponentScript("Ref_KickOffV", gOppoConfig.KickOff(), 1)
else
	gCurrentPlay = cond.getOpponentScript("Ref_KickOffV", gOppoConfig.KickOff, 1)
end