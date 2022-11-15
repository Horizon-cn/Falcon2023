-- 在进入每一个定位球时，需要在第一次进时进行保持
--need to modify
-- if math.abs(ball.refPosY()) < 200 then
-- 	dofile("./lua_scripts/ssl/play/Ref/FrontKick/FrontKick.lua")
-- else

function isCorner()
    if 8*math.abs(ball.refPosX())+3*math.abs(ball.refPosY()) >= 4200 then
        return true
    else
        return false
    end
end
if isCorner() and ball.refPosX()>=0 then
	dofile("./lua_scripts/ssl/play/Ref/CornerKick/CornerKick.lua")

elseif ball.refPosX()>200 then
	dofile("./lua_scripts/ssl/play/Ref/FrontKick/FrontKick.lua")
elseif ball.refPosX() < 200 and ball.refPosX() > -200 then
	dofile("./lua_scripts/ssl/play/Ref/MiddleKick/MiddleKick.lua")
else
	dofile("./lua_scripts/ssl/play/Ref/BackKick/BackKick.lua")
end
gOurIndirectTable.lastRefCycle = vision:Cycle()
