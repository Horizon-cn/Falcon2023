local WAIT_BALL_POS = function(anti)
  return function()
    return ball.pos() + Utils.Polar2Vector(50, anti * math.pi)
  end
end
local SHOOT_POS = ball.syntYPos(CGeoPoint:new_local(520/1200*param.pitchLength,0/900*param.pitchWidth))
-- local function def_chipPower()
--   if math.abs(ball.posY()) > 300 then 
--     return 350
--   elseif math.abs(ball.posY())> 285 then
--     return 220
--   elseif math.abs(ball.posY()) > 270 then 
--     return 200
--   else 
--     return 20
--   end
-- end
local KICK_POWER=function()
  return 20*math.sqrt(ball.toPointDist(SHOOT_POS()))
end

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"] = {
    switch = function()
      if bufcnt(player.toTargetDist("Assister") < 20 , 10, 180) then
        return "toBall"
      end
    end,
    Assister = task.goCmuRush(WAIT_BALL_POS(1),player.toPointDir(SHOOT_POS),_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.markingFront("First"),
    Middle   = task.markingFront("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "[D][A][SBC][LM]"
  },

  ["toBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Assister", ball.pos()) < 20, 100, 500) then
        return "leaveBall"
      end
    end,
    Assister = task.staticGetBall(SHOOT_POS),
    Leader   = task.markingFront("First"),
    Middle   = task.markingFront("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "[D][A][SBC][LM]"
  },

  ["leaveBall"] = {
    switch = function ()
      if bufcnt(player.kickBall("Assister"), 3, 180) then
        return "exit"
      end
    end,
    Assister = task.chipPass(SHOOT_POS,KICK_POWER),
    Leader   = task.markingFront("First"),
    Middle   = task.markingFront("Second"),
    Special  = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match = "[D][A][SBC][LM]"
  },

  name = "Ref_IndirectCornerPush8",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
