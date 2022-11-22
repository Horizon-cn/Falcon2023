function TimeDelayTest(task)

  local mflag = 0
  
  execute = function(runner)
    return CTimeDelayTest(runner, mflag)
  end
  
  matchPos = function()
    return CGeoPoint:new_local(0,0)
  end
    
  return execute, matchPos

end
  
gSkillTable.CreateSkill{
    name = "TimeDelayTest",
    execute = function (self)
      print("This is in skill"..self.name)
    end
}