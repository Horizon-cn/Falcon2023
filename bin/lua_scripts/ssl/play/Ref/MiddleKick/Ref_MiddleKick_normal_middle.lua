local RECEIVE_POS = ball.syntYPos(CGeoPoint:new_local(550, 120))
local BLOCK_POS = ball.syntYPos(CGeoPoint:new_local(0, 350))
local BLOCK_POS2 = ball.syntYPos(CGeoPoint:new_local(420, 0))
local RECEIVE_POS2 = ball.syntYPos(CGeoPoint:new_local(300, 250))
local BARYCENTER = ball.syntYPos(CGeoPoint:new_local(275, 175))
local SHOOT_POS = ball.syntYPos(CGeoPoint:new_local(510, 70))
local kickPower = 300
gPlayTable.CreatePlay{

  firstState = "get",

  ["get"] = {
    switch = function()
      if bufcnt(ball.toPlayerHeadDist("Assister") < 5 and player.toTargetDist("Special") < 20 and player.toTargetDist("Leader") < 20,"fast",180) then
        return "move"
      end
    end,
    Assister = task.staticGetBall(RECEIVE_POS),
    Special  = task.goCmuRush(BLOCK_POS,_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.goCmuRush(BARYCENTER,_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    Goalie   = task.goalieNew(),
    match    = "[A][S][D][L][B][C][M]"
  },

  ["move"]= {
    switch = function()
      if bufcnt(player.toTargetDist("Special") < 20, 10, 180) then
        return "receive"
      end
    end,
    Assister = task.staticGetBall(RECEIVE_POS),
    Special  = task.goCmuRush(RECEIVE_POS2,_,_,flag.allow_dss + flag.dodge_ball),
    Leader   = task.stop(),
    Middle   = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    match    = "[A][S][D][L][B][C][M]"
  },

  ["receive"]= {
    switch = function()
      if bufcnt(ball.toPlayerHeadDist("Special") < 5, "fast", 180) then
        return "shoot"
      end
    end,
    Assister = task.chipPass(RECEIVE_POS2,kickPower),
    Special  = task.receive(ball.pos(),RECEIVE_POS2),
    Leader   = task.goCmuRush(BLOCK_POS2,_,_,flag.allow_dss + flag.dodge_ball),
    Middle   = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    match    = "[A][S][D][L][B][C][M]"
  },

  ["shoot"]= {
    switch = function()
      if bufcnt(player.kickBall("Special"), 3, 180) then
        return "exit"
      end
    end,
    Assister = task.defendHead(),
    Special  = task.chipPass(SHOOT_POS,kickPower),
    Leader   = task.defendHead(),
    Middle   = task.multiBack(4,1),
    Defender = task.multiBack(4,2),
    Breaker  = task.multiBack(4,3),
    Crosser  = task.multiBack(4,4),
    match    = "[A][S][D][L][B][C][M]"
  },

  name = "Ref_MiddleKick_normal_middle",
  applicable = {
    exp = "a",
    a   = true
  },
  attribute = "attack",
  timeout = 99999

}
