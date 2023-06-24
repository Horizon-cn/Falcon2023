if type(gOppoConfig.IndirectBackKick) == "function" then
  gCurrentPlay = cond.getOpponentScript("Ref_IndirectBackKickV", gOppoConfig.IndirectBackKick(), 3)
else
  gCurrentPlay = cond.getOpponentScript("Ref_IndirectBackKickV", gOppoConfig.IndirectBackKick, 3)
end
