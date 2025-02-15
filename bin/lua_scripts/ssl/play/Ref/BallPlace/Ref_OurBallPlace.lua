local BALL_PLACE_FLAG = bit:_or(flag.dodge_ball,flag.allow_dss)
local LEADER_TASK = function()
	return task.fetchBall(ball.placementPos())
end

local PointA = CGeoPoint:new_local(0/1200*param.pitchLength,-150/900*param.pitchWidth)
local PointB = CGeoPoint:new_local(0/1200*param.pitchLength,150/900*param.pitchWidth)
gPlayTable.CreatePlay{

firstState = "start",

["start"] = {
	switch = function()
		return "start"
	--   if ball.toPointDist(ball.placementPos())<=400  then
	--     return "beginning2"
	--   else 
	--     return "beginning2"
	--   end
	end,
	Leader   = LEADER_TASK(),
	Assister = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
	Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
	Defender000Middle000Engine000Powerhouse = combo.multiBack(4),
	Goalie   = task.goalieNew(),
	match    = "{LA}[SDMEP]"
},

-- ["beginning1"] ={
-- switch = function()
--        if bufcnt(player.toTargetDist("Leader") < 20 , 20) then
--        return "pass"
--      end
--   end,
--     Leader   = LEADER_TASK(),
--     --Leader =   task.getBall(),
--     Assister = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG),
--     Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
--     Defender = task.leftBack(),
--     Middle   = task.rightBack(),
--     Engine   = task.goLeftSupport(),
--     Powerhouse = task.goRightSupport(),
--     Goalie   = task.goalieNew(),
--     match    = "{LA}[SDMEP]"
--     --match    = "{LA} "
-- }, 

-- ["pass"] ={
-- switch = function()
--         if player.kickBall("Leader") then
--            return "receive1"
--         end
--         --if bufcnt(ball.toPlayerHeadDist("Assister") < 200, "fast") then
--           --return "place1"
--         --end
--       end,
--     Leader   = task.flatPass("Assister",600),
--     --Leader   = task.passToPos(ball.placementPos(),500),
--     Assister = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG), 
--     Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
--     Defender = task.leftBack(),
--     Middle   = task.rightBack(),
--     Engine   = task.goLeftSupport(),
--     Powerhouse = task.goRightSupport(),
--     Goalie   = task.goalieNew(),
--     match    = "{LA}[SDMEP]"
--     --match    = "{LA}"
-- }, 

-- ["receive1"] ={
-- switch = function()
--  if bufcnt(ball.toPlayerHeadDist("Assister") <100, "fast",1000) then
--       return "place1"
--    end
--  end,
--    Leader   = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
--    Assister = task.receivePass("Leader"),
--    Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
--    Defender = task.leftBack(),
--    Middle   = task.rightBack(),
--     Engine   = task.goLeftSupport(),
--     Powerhouse = task.goRightSupport(),
--     Goalie   = task.goalieNew(),
--     match    = "{LA}[SDMEP]"
--    --match    = "{LA}"
-- }, 

-- ["place1"] ={
-- switch = function()
--   if cond.isGameOn() and cond.theirBallPlace() then
--       return "exit"
--    end
--  end,
--     Leader   = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG),
--     Assister = LEADER_TASK(),
--     Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
--     Defender = task.leftBack(),
--     Middle   = task.rightBack(),
--     Engine   = task.goLeftSupport(),
--     Powerhouse = task.goRightSupport(),
--     Goalie   = task.goalieNew(),
--     match    = "{LA}[SDMEP]"
--     --match    = "{LA}"
-- }, 

-- ["beginning2"] = {
-- switch = function()
--        if  bufcnt(player.toTargetDist("Leader") < 20 , 20) then
--         return "place2"
--        end
--     end,
--     Leader   = LEADER_TASK(),
--     Assister = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG),
--     Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
--     Defender = task.leftBack(),
--     Middle   = task.rightBack(),
--     Engine   = task.goLeftSupport(),
--     Powerhouse = task.goRightSupport(),
--     Goalie   = task.goalieNew(),
--     match    = "{LA}[SDMEP]"
--     --match    = "{LA}"
-- },


-- ["place2"] = {
-- switch = function()
--   if cond.theirBallPlace() then
--    return "exit"
--   end
-- end,
--   Leader     = LEADER_TASK(),
--   Assister = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG),
--   Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
--   Defender = task.leftBack(),
--   Middle   = task.rightBack(),
--     Engine   = task.goLeftSupport(),
--     Powerhouse = task.goRightSupport(),
--     Goalie   = task.goalieNew(),
--     match    = "{LA}[SDMEP]"
--   --match    = "{LA}"
-- },

name = "Ref_OurBallPlace",
applicable ={
  exp = "a",
  a   = true
},
attribute = "defense",
timeout   = 99999
}