-- 在进入每一个定位球时，需要在第一次进时进行保持
--need to modify
-- if math.abs(ball.refPosY()) < 200 then
-- 	dofile("./lua_scripts/ssl/play/Ref/FrontKick/FrontKick.lua")
-- else

function isCorner()
    if ball.refPosX() < -360 and math.abs(ball.refPosY()) > 200 then
        return true
    else
        return false
    end
end
if ball.refPosX() > 360 and math.abs(ball.refPosY()) > 220 then
	dofile("../lua_scripts/ssl/play/Ref/DirectCornerKick/DirectCornerKick.lua")
elseif ball.refPosX()>0 then
	dofile("../lua_scripts/ssl/play/Ref/DirectFrontKick/DirectFrontKick.lua")
else
	dofile("../lua_scripts/ssl/play/Ref/DirectBackKick/DirectBackKick.lua")
end
gOurIndirectTable.lastRefCycle = vision:Cycle()