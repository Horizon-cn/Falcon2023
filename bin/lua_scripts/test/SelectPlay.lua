-- 第一次执行时，检查gReadyPlay是否合格，不合格则不再运行脚本
if gLastCycle == 0 then
	assert(NeedExit(gReadyPlay) == false, debugEngine:gui_debug_msg(CGeoPoint:new_local(-param.pitchLength/2,-param.pitchWidth/2),"gReadyPlay can't run",0))
end
-- 检查脚本运行的环境
checkPlayENV()
-- 脚本退出时的处理
if NeedExit(gCurrentPlay) then
	gCurrentPlay = gReadyPlay
	ResetPlay(gCurrentPlay)
end
gLastPlay = gCurrentPlay
RunPlay(gCurrentPlay)
debugEngine:gui_debug_msg(CGeoPoint:new_local(-50, -param.pitchWidth/2-20),gCurrentPlay)
debugEngine:gui_debug_msg(CGeoPoint:new_local(-50, -param.pitchWidth/2),gCurrentState)
