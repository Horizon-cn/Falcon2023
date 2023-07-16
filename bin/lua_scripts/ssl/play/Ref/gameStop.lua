-- 1200*900 used
if OPPONENT_NAME == "PureDefence8" then
     if ball.refPosX() < -480/1200*param.pitchLength and math.abs(ball.refPosY()) > 300/900*param.pitchWidth then
            gCurrentPlay = "Ref_CornerDef_PureDefence8"
        elseif ball.refPosX() > 100/1200*param.pitchLength then
            gCurrentPlay = "Ref_FrontDef_PureDefence8"
        elseif ball.refPosX() >-100/1200*param.pitchLength then
            gCurrentPlay = "Ref_MiddleDef_PureDefence8"
        else
            gCurrentPlay = "Ref_BackDef_PureDefence8"
        end
elseif OPPONENT_NAME == "NormalKick" then
    gCurrentPlay = "Ref_Stop_normal"
else
    gCurrentPlay = "Ref_Stop_normal"
end