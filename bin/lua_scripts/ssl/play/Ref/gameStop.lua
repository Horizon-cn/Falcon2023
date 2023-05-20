-- change to double size by hjp
-- function isCorner()
--     if 8*math.abs(ball.refPosX())+3*math.abs(ball.refPosY()) >= 4200 then
--         return true
--     else
--         return false
--     end
-- end

-- if OPPONENT_NAME == "other" or OPPONENT_NAME == "Avoidfoul" then
--     if isCorner() and ball.refPosX()>=0 then
--         gCurrentPlay = "Ref_Stop4CornerKick"
--     elseif math.abs(ball.refPosY()) > 410 then
--         gCurrentPlay = "Ref_Stop4SideLine"
--     elseif ball.refPosX()>200 then
--         gCurrentPlay = "Ref_Stop4FrontKick" 
--     elseif ball.refPosX() < 200 and ball.refPosX() > -200 then
--         gCurrentPlay = "Ref_Stop4MiddleKick"
--     else
--         gCurrentPlay = "Ref_Stop4BackKick"

--     end
-- else
-- --技术挑战赛
--     gCurrentPlay = "Ref_Stop4ChaKick"
-- end

-- change to double size by yys
-- 900*600 used
if OPPONENT_NAME == "PureDefence" then
    if ball.refPosX() < -360 and math.abs(ball.refPosY()) > 200 then
        gCurrentPlay = "Ref0_Stop4CornerDef"
    elseif ball.refPosX() > 360 and math.abs(ball.refPosY()) > 220 then
        gCurrentPlay = "Ref0_Stop4CornerKick"
    elseif ball.refPosX() < -(param.pitchLength/2 - param.penaltyDepth - 100) and -(param.pitchLength/2 - param.penaltyDepth)<= ball.refPosX() and math.abs(ball.refPosY()) < param.penaltyWidth/2 + 100 then
        gCurrentPlay = "Ref0_StopV3"
    else
        gCurrentPlay = "Ref0_StopV2"
    end
else
    if ball.refPosX() < -360 and math.abs(ball.refPosY()) > 200 then
        gCurrentPlay = "Ref_Stop4CornerDef"
    elseif ball.refPosX() > 360 and math.abs(ball.refPosY()) > 220 then
        gCurrentPlay = "Ref_Stop4CornerKick"
    elseif ball.refPosX() < -(param.pitchLength/2 - param.penaltyDepth - 100) and -(param.pitchLength/2 - param.penaltyDepth)<= ball.refPosX() and math.abs(ball.refPosY()) < param.penaltyWidth/2 + 100 then
        gCurrentPlay = "Ref_StopV3"
    else
        gCurrentPlay = "Ref_StopV2"
    end
end
-- 避免犯规：过于接近球
-- gCurrentPlay = "Ref_StopBack"