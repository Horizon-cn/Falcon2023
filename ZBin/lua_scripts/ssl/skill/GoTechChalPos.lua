function GoTechChalPos(task)
	execute = function(runner)
		return CGoTechChalPos(runner)
	end

	matchPos = function(runner)
		return ball.pos()
	end

	return execute, matchPos
end

gSkillTable.CreateSkill{
	name = "GoTechChalPos",
	execute = function (self)
		print("This is in skill"..self.name)
	end
}