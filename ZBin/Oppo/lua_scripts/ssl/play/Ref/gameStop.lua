-- change to double size by hjp
function isCorner()
    if 8*math.abs(ball.refPosX())+3*math.abs(ball.refPosY()) >= 4200 then
        return true
    else
        return false
    end
end

if OPPONENT_NAME == "other" then
    if isCorner() and ball.refPosX()<0 then
        gCurrentPlay = "Ref_Stop4CornerDef"
    elseif isCorner() and ball.refPosX()>=0 then
        gCurrentPlay = "Ref_Stop4CornerKick"
    elseif math.abs(ball.refPosY()) > 410 then
        gCurrentPlay = "Ref_Stop4SideLine"
    elseif ball.refPosX()>200 then
        gCurrentPlay = "Ref_Stop4FrontKick" 
    elseif ball.refPosX() < 200 and ball.refPosX() > -200 then
        gCurrentPlay = "Ref_Stop4MiddleKick"
    else
        gCurrentPlay = "Ref_Stop4BackKick"

    end
else
--技术挑战赛
    gCurrentPlay = "Ref_Stop4ChaKick"
end