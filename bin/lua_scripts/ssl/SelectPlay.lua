gNormalPlay = gOppoConfig.NorPlay

function RunRefScript(name)
	local filename = "../lua_scripts/ssl/play/Ref/"..name..".lua"
	dofile(filename)
end

function SelectRefPlay()
	local curRefMsg = vision:GetCurrentRefereeMsg()
	if curRefMsg == "" then
		--print("didn't receive curRefMsg!!!")
		return false
	end

	if curRefMsg == "ourIndirectKick" and gLastRefMsg ~= curRefMsg then
		gIsOurIndirectKickExit = false
	end

	if curRefMsg == "ourIndirectKick" and gIsOurIndirectKickExit then
		return false
	end

	if gLastRefMsg ~= curRefMsg or curRefMsg == "gameStop" then
		ball.updateRefMsg()
	end

	RunRefScript(curRefMsg)
	gLastRefMsg = curRefMsg
	return true
end

function SelectBayesPlay()
	gCurrentPlay = gNormalPlay
	ResetPlay(gCurrentPlay)
end


---------------------------------------
--选play
--------------------------------------
if SelectRefPlay() then
	-- or NeedExit(gCurrentPlay)不添加会出问题！！
	if gCurrentPlay ~= gLastPlay or NeedExit(gCurrentPlay) then
		ResetPlay(gCurrentPlay)
		if vision:GetCurrentRefereeMsg() == "ourIndirectKick" then
			gIsOurIndirectKickExit = true
		end
		print("New Play: "..gCurrentPlay)
	end
else
	if IS_TEST_MODE then
		if gLastPlay == "" or NeedExit(gCurrentPlay) then
			debugEngine:gui_debug_msg(CGeoPoint:new_local(-param.pitchLength/2,-param.pitchWidth/2),'TEST_MODE',0)
			if type(gTestPlay) == "string" then
				gCurrentPlay = gTestPlay
			elseif type(gTestPlay) == "function" then
				gCurrentPlay = gTestPlay()
			end
		end
		if gCurrentPlay ~= gLastPlay or
			NeedExit(gCurrentPlay) then
			ResetPlay(gCurrentPlay)
		end
	else
		if gLastPlay == "" or NeedExit(gCurrentPlay) then
			print("Play: "..gCurrentPlay.." Exit!!")
			SelectBayesPlay()
		end
	end
end

gLastPlay = gCurrentPlay
			
RunPlay(gCurrentPlay)

debugEngine:gui_debug_msg(CGeoPoint:new_local(-50, -param.pitchWidth/2),gCurrentState)
