-- --ball.placementPos():x(), ball.placementPos():y()
-- if ball.placementPos():x() < -450 and math.abs(ball.placementPos():y()) > 380 then
-- 	gCurrentPlay = "Ref_OurBallPlace4CornerDefV2"
-- elseif ball.placementPos():x() > 450 and math.abs(ball.placementPos():y())> 380 then
-- 	gCurrentPlay = "Ref_OurBallPlace4CornerKickV2"
-- else
-- 	gCurrentPlay = "Ref_OurBallPlaceV3.2"
-- end
--if ball.pos():y() < param.pitchWidth/2-10 and ball.pos():y() >-param.pitchWidth/2+10 then
-- 	gCurrentPlay = "Ref_OurBallPlace"
-- --边线球：：：：
-- else
-- 	gCurrentPlay = "Ref_OurBallPlaceV2"
-- end

print(vision:next_gameState():get())
gCurrentPlay = "Ref_OurBallPlaceV2"
	--gCurrentPlay = "Ref_BallPassandPlace"

