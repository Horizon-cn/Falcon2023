if OPPONENT_NAME == "NormalKick" then
	if ball.refPosX() > 480/1200*param.pitchLength and math.abs(ball.refPosY()) > 300/900*param.pitchWidth then
	    dofile("../lua_scripts/ssl/play/Ref/CornerKick/CornerKick.lua")
	elseif ball.refPosX() > 100/1200*param.pitchLength then
	    dofile("../lua_scripts/ssl/play/Ref/FrontKick/FrontKick.lua")
	elseif ball.refPosX()>-100/1200*param.pitchLength then
	    dofile("../lua_scripts/ssl/play/Ref/MiddleKick/MiddleKick.lua")
	else
	    dofile("../lua_scripts/ssl/play/Ref/BackKick/BackKick.lua")
	end
else
	if ball.refPosX() > 480/1200*param.pitchLength and math.abs(ball.refPosY()) > 300/900*param.pitchWidth then
		dofile("../lua_scripts/ssl/play/Ref/CornerKick/CornerKick.lua")
	elseif ball.refPosX()>0 then
		dofile("../lua_scripts/ssl/play/Ref/FrontKick/FrontKick.lua")
	else
		dofile("../lua_scripts/ssl/play/Ref/BackKick/BackKick.lua")
	end
end