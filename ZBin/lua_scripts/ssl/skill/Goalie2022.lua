function Goalie2022(task)
	local mflag = task.flag or 0

	execute = function(runner)
		return CGoalie2022(runner, mflag)
	end

	matchPos = function()
		return pos.goaliePos()
	end

	return execute, matchPos
end

gSkillTable.CreateSkill{
	name = "Goalie2022",
	execute = function (self)
		print("This is in skill"..self.name)
	end
}
