function GoSupport(task)

  execute = function(runner)
    return CGoSupport(runner, task.direction)
  end

  matchPos = function()
    if task.direction == 1 then
      return pos.supportLeftPos2022()
    else
      return pos.supportRightPos2022()
    end
  end
  return execute, matchPos
end

gSkillTable.CreateSkill{
  name = "GoSupport",
  execute = function (self)
    print("This is in skill"..self.name)
  end
}