function Break(task)
    local targetPos
  
    execute = function(runner)
      if type(targetPos) == "function" then
        targetPos = task.pos()
      else
        targetPos = task.pos
      return CBreak(runner, targetPos:x(), targetPos:y())
    end
  
    matchPos = function()
      
      return ball.pos()
    end
    
    return execute, matchPos
  end
  
gSkillTable.CreateSkill{
    name = "Break",
    execute = function (self)
      print("This is in skill"..self.name)
    end
}