--Back是靠近我們球門的(對面進攻)
if ball.posX() > 100 then 
	 dofile("../lua_scripts/ssl/play/Ref/FrontDef/FrontDef.lua")
elseif ball.posX() > -100 then
	dofile("../lua_scripts/ssl/play/Ref/MiddleDef/MiddleDef.lua")
elseif ball.posX() < -300 and math.abs(ball.posY()) > 120  then 
	dofile("../lua_scripts/ssl/play/Ref/CornerDef/CornerDef.lua")
elseif ball.posX() < -300 and math.abs(ball.posY()) < 120 then 
	dofile("../lua_scripts/ssl/play/Ref/BackDef/BackDef.lua")
else 
	dofile("../lua_scripts/ssl/play/Ref/BackDef/BackDef.lua")
end