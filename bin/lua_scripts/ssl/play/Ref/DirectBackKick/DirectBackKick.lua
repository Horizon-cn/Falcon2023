if type(gOppoConfig.DirectBackKick) == "function" then
  gCurrentPlay = cond.getOpponentScript("Ref_DirectBackKickV", gOppoConfig.DirectBackKick(), 3)
else
  gCurrentPlay = cond.getOpponentScript("Ref_DirectBackKickV", gOppoConfig.DirectBackKick, 3)
end
