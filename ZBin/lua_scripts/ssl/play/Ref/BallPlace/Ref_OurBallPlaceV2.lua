local BALL_PLACE_FLAG = bit:_or(flag.dodge_ball,flag.allow_dss)
--local BALL_PLACE_FLAG = 0
local LEADER_TASK = function()
  return task.fetchBall(ball.placementPos())
end

--local GET_BALL=function ()
 -- return task.getBall()
--end
local PointA = CGeoPoint:new_local(0, -150)
local PointB = CGeoPoint:new_local(0, 150)
gPlayTable.CreatePlay{

firstState = "start",

   

["start"] = {
switch = function()
      --print("lsp_ballplacement")
      if ball.toPointDist(ball.placementPos())<=400  then
        return "beginning2"
      else 
        return "beginning1"
      end
    end,
   -- Leader   = GET_BALL(),
    --此处上方可能ball，placement使用错误
    Leader   = LEADER_TASK(),
    Assister = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG),
    --Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    --Defender = task.leftBack(),
    --Middle   = task.rightBack(),
    --Goalie   = task.goalie(),
    --match    = "{LA}[SDMG]"
    match    = "{LA}"
},

["beginning1"] ={
switch = function()
       if bufcnt(player.toTargetDist("Leader") < 20 , 20) then
       return "pass"
     end
  end,
    --Leader   = GET_BALL(),
    --此处上方可能ball，placement使用错误
    Leader   = LEADER_TASK(),
    --Leader =   task.getBall(),
    Assister = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG),
   -- Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
   -- Defender = task.leftBack(),
    --Middle   = task.rightBack(),
   -- Goalie   = task.goalie(),
    --match    = "{LA}[SDMG]"
    match    = "{LA} "
}, 

["pass"] ={
switch = function()
        if player.kickBall("Leader") then
           return "receive1"
        end
        --if bufcnt(ball.toPlayerHeadDist("Assister") < 200, "fast") then
          --return "place1"
        --end
      end,
    Leader   = task.flatPass("Assister",600),
    --Leader   = task.passToPos(ball.placementPos(),500),
    Assister = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG), 
    --Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    --Defender = task.leftBack(),
    --Middle   = task.rightBack(),
    --Goalie   = task.goalie(),
    --match    = "{LA}[SDMG]"
    match    = "{LA}"
}, 

["receive1"] ={
switch = function()
 if bufcnt(ball.toPlayerHeadDist("Assister") <100, "fast",1000) then
      return "place1"
   end
 end,
   Leader   = task.goCmuRush(PointA, dir.playerToBall, ACC, BALL_PLACE_FLAG),
   Assister = task.receivePass("Leader"),
    --Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    --Defender = task.leftBack(),
    --Middle   = task.rightBack(),
    --Goalie   = task.goalie(),
    --match    = "{LA}[SDMG]"
   match    = "{LA}"
}, 

["place1"] ={
switch = function()
  if cond.isGameOn() and cond.TheirBallPlace() then
      return "exit"
   end
 end,
    Leader   = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG),
    Assister = LEADER_TASK(),
    --Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    --Defender = task.leftBack(),
    --Middle   = task.rightBack(),
    --Goalie   = task.goalie(),
    --match    = "{LA}[SDMG]"
    match    = "{LA}"
}, 

["beginning2"] = {
switch = function()
       if  bufcnt(player.toTargetDist("Leader") < 20 , 20) then
        return "place2"
       end
    end,
    Leader   = LEADER_TASK(),
    Assister = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG),
    --Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
    --Defender = task.leftBack(),
    --Middle   = task.rightBack(),
    --Goalie   = task.goalie(),
    --match    = "{LA}[SDMG]"
    match    = "{LA}"
},


["place2"] = {
switch = function()
  if cond.isGameOn() and cond.TheirBallPlace() then
   return "exit"
  end
end,
  Leader     = LEADER_TASK(),
  Assister = task.goCmuRush(ball.readyplacementPos(), dir.playerToBall, ACC, BALL_PLACE_FLAG),
  --Special  = task.goCmuRush(PointB, dir.playerToBall, ACC, BALL_PLACE_FLAG),
  --Defender = task.leftBack(),
  --Middle   = task.rightBack(),
  --Goalie   = task.goalie(),
  --match    = "{LA}[SDMG]"
  match    = "{LA}"
},


name = "Ref_OurBallPlaceV2",
applicable ={
  exp = "a",
  a   = true
},
attribute = "defense",
timeout   = 99999
}