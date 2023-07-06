local DetectTheSupportID = function() 
    if ball.posX() > 200 and ball.posY() < -120 then  -- 在0号区域
        return 2  -- 往2号区域打
    elseif ball.posX() > 200 and ball.posY() < 120 then -- 在1号区域
        if ball.posX() > 0 then
            return 2
        else 
            return 0
        end
    elseif ball.posX() > 200 and ball.posY() >= 120 then -- 在2号区域
        return 0 -- 往0号打
    elseif ball.posX() > -200 and ball.posY() < -120 then -- 在3号区域
        return 0 -- 往0号打
    elseif ball.posX() > -200 and ball.posY() < 120 then -- 在4号区域
        return 1 -- 往1号打
    elseif ball.posX() > -200 and ball.posY() >= 120 then -- 在5号区域
        return 2 -- 往2号打
    else
        return 4 -- 往4号打
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
    Leader =  task.support("Leader", DetectTheSupportID),--task.markingFront("Second"),
    Assister = task.defendMiddle(), --改跑點
    Middle =  task.defendKick(), 
    Special = task.sideBackUltra(),--task.markingFront("First"),
    Defender = task.multiBack(3,1),
    Crosser  = task.multiBack(3,2),
    Breaker  = task.multiBack(3,3),
    Goalie = task.goalieNew(),
    match = "[DC][M][L][A][B][S]"
},
  name = "Ref_FrontDef_normal",
  applicable = {
    exp = "a",
    a = true
  },
  attribute = "defense",
  timeout = 99999
}