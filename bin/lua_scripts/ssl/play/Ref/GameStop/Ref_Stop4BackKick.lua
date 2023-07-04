--无人维护
local SIDE_POS, MIDDLE_POS, INTER_POS, SIDE2_POS, INTER2_POS = pos.refStopAroundBall()

local STOP_FLAG = flag.dodge_ball
local STOP_DSS = bit:_or(STOP_FLAG, flag.allow_dss)

local OTHER_SIDE_POS = function()
  local factor = 1
  if ball.posY() > 0 then
    factor = -1
  end
  return CGeoPoint:new_local(INTER_POS():x(), factor * param.pitchWidth * 0.35)
end

local ACC = 300
local waitpos = ball.refSyntYPos(CGeoPoint:new_local(-415/1200*param.pitchLength,415/900*param.pitchWidth))

gPlayTable.CreatePlay {

firstState = "IndirectBackKickStop",

["IndirectBackKickStop"] = {
  switch = function()
    if cond.isGameOn() then
      return "exit"
    else
      return "IndirectBackKickStop"
    end
  end,

  Assister = task.goCmuRush(MIDDLE_POS, dir.playerToBall, ACC, STOP_DSS),
  Special  = task.goCmuRush(INTER_POS, dir.playerToBall, ACC, STOP_DSS),
  Engine   = task.multiBack(2,1),
  Hawk     = task.multiBack(2,2),
  Leader   = task.goCmuRush(OTHER_SIDE_POS, dir.playerToBall, ACC, STOP_DSS),
  Defender  = task.goCmuRush(ball.refAntiYPos(CGeoPoint:new_local(-270/1200*param.pitchLength,210/900*param.pitchWidth))),
  Middle   = task.goCmuRush(waitpos, dir.playerToBall, ACC, STOP_DSS),
  Goalie   = task.goalieNew(),
  match    = "[A][H][E][S][M][DL]"
},


name = "Ref_Stop4BackKick",
applicable = {
  exp = "a",
  a = true
},
attribute = "attack",
timeout = 99999
}
