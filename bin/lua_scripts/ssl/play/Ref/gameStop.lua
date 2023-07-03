local ourDirectKick=vision:next_gameState():ourDirectKick()
local ourIndirectKick=vision:next_gameState():ourIndirectKick()
local theirDirectKick=vision:next_gameState():theirDirectKick()
local theirIndirectKick=vision:next_gameState():theirIndirectKick()
-- 1200*900 used
if OPPONENT_NAME == "PureDefence8" then
     if ball.refPosX() < -480 and math.abs(ball.refPosY()) > 300 then
            gCurrentPlay = "Ref_StopCornerDefPureDefence"
        elseif ball.refPosX() > 0 and math.abs(ball.refPosY()) < 300 then
            gCurrentPlay = "Ref_FrontDef8"
        elseif ball.refPosX() < 0 then
            gCurrentPlay = "Ref_BackDef8"
        elseif ball.refPosX() < -(param.pitchLength/2 - param.penaltyDepth - 100) and -(param.pitchLength/2 - param.penaltyDepth)<= ball.refPosX() and math.abs(ball.refPosY()) < param.penaltyWidth/2 + 100 then
            gCurrentPlay = "Ref_StopV3_normal"
        else
            gCurrentPlay = "Ref_StopV2_normal"
        end
elseif OPPONENT_NAME == "NormalKick" then
    if ourDirectKick then
        if ball.refPosX() > 480 and math.abs(ball.refPosY()) > 300 then
            gCurrentPlay = "Ref_Stop4CornerKick"
        elseif ball.refPosX() > 100 then
            gCurrentPlay = "Ref_Stop4FrontKick"
        elseif ball.refPosX()>-100 then
            gCurrentPlay = "Ref_Stop4MiddleKick"
        else
            gCurrentPlay = "Ref_Stop4BackKick"
        end
    elseif ourIndirectKick then
        if ball.refPosX() > 480 and math.abs(ball.refPosY()) > 300 then
            gCurrentPlay = "Ref_Stop4CornerKick"
        elseif ball.refPosX() > 100 then
            gCurrentPlay = "Ref_Stop4FrontKick"
        elseif ball.refPosX()>-100 then
            gCurrentPlay = "Ref_Stop4MiddleKick"
        else
            gCurrentPlay = "Ref_Stop4BackKick"
        end
    elseif theirDirectKick or theirIndirectKick then
        if ball.refPosX() < -200 and (ball.refPosY() < -300 or ball.refPosY() > 300 ) then
            gCurrentPlay = "Ref_Stop4CornerDef_play8"
        elseif ball.refPosX() < -200 and (ball.refPosY() > -300 and ball.refPosY() < 300 ) then
            gCurrentPlay = "Ref_Stop4BackDef_play8" 
        elseif ball.refPosX() >-200 and ball.refPosX() < 200 then
            gCurrentPlay = "Ref_Stop4MiddleDef_play8"
        elseif ball.refPosX() > 200 then
            gCurrentPlay = "Ref_Stop4FrontDef_play8"
        else
            gCurrentPlay = "Ref_Stop4BackDef_play8"
        end
    else
        gCurrentPlay = "Ref_StopV2_Play8"
    end
else
    gCurrentPlay = "Ref_StopV2_normal"
end
