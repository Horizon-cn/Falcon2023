function Rush(task)
  local mpos
  local mflag = task.flag or 0

  execute = function(runner)
    if type(task.pos) == "function" then
      mpos = task.pos()
    else
      mpos = task.pos
    end
    return CRush(runner, mpos:x(), mpos:y(), mflag)
  end

  matchPos = function()
    if type(task.pos) == "function" then
      mpos = task.pos()
    else
      mpos = task.pos
    end
    return mpos
  end

  return execute, matchPos
end

gSkillTable.CreateSkill{
  name = "Rush",
  execute = function (self)
    print("This is in skill"..self.name)
  end
}