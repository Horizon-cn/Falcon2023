local SHOOT_POS = function()
  if math.abs(ball.posX()) < 0 then
    return ball.antiYPos(CGeoPoint:new_local(0/1200*param.pitchLength,0/900*param.pitchWidth))()
  else 
    return ball.syntYPos(CGeoPoint:new_local(500/1200*param.pitchLength,0/900*param.pitchWidth))()
  end
end

gPlayTable.CreatePlay{

  firstState = "start",

  ["start"]= {
  switch = function()
      if cond.isGameOn() then
        return "exit"
      end
    end,
  Leader = task.sideBack(),
  Hawk = task.multiBack(3,1),
  Middle = task.multiBack(3,2),
  Special = task.goCmuRush(WAIT_BALL_POS,player.toPointDir(SHOOT_POS),_,flag.allow_dss + flag.dodge_ball),
  Assister = task.markingFront("First"),
  Powerhouse = task.markingFront("Second"),
  Defender = task.defendKick(),
  Goalie = task.goalieNew(),
  match    = "[HM][D][L][S][AP]"
},
  name = "Ref_MiddleDef8",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}
