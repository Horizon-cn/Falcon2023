-- 在进入每一个定位球时，需要在第一次进时进行保持
--need to modify
--refPosY()
--refPosX()
--Back是靠近我們球門的(對面進攻)
gNorPass2NorDefBallVel = 80
if ball.refPosX() < -200/1200*param.pitchLength and (ball.refPosY() < -220/900*param.pitchWidth or ball.refPosY() > 220/900*param.pitchWidth ) then
	dofile("../lua_scripts/ssl/play/Ref/CornerDef/CornerDef.lua")--主要配合MultiDefend_8
elseif ball.refPosX() < -200/1200*param.pitchLength and (ball.refPosY() > -220/900*param.pitchWidth and ball.refPosY() < 220/900*param.pitchWidth ) then 
	dofile("../lua_scripts/ssl/play/Ref/BackDef/BackDef.lua") --主要配合MultiDefend_8
elseif ball.refPosX() >-200/1200*param.pitchLength and ball.refPosX() < 200/1200*param.pitchLength then
	dofile("../lua_scripts/ssl/play/Ref/MiddleDef/MiddleDef.lua")--主要配合MiddleDefendBalance_8
elseif ball.refPosX() > 200/1200*param.pitchLength then 
	dofile("../lua_scripts/ssl/play/Ref/FrontDef/FrontDef.lua")--主要配合MiddleAttack_8
else 
	dofile("../lua_scripts/ssl/play/Ref/BackDef/BackDef.lua")--主要配合MultiDefend_8
end
