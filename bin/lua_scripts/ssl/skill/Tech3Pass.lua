function Tech3Pass(task)
	execute=function(runner)
		return CTech3Pass(runner)
	end
	matchPos=function()
		return ball.pos()
	end
	return execute,matchPos
end

gSkillTable.CreateSkill{
	name = "Tech3Pass",
	execute= function(self)
		print("This is in skill"..self.name)
	end
}