function SpeedTest(task)
	execute = function(runner)
		return CSpeedTest(runner, task.p1:x(),task.p1:y(),task.p2:x(),task.p2:y(),task.v1,task.v2,task.v_step)
	end
	matchPos = function()
		return pos.goaliePos()
	end
	return execute, matchPos
end

gSkillTable.CreateSkill{
	name = "SpeedTest",
	execute = function (self)
		print("This is in skill"..self.name)
	end
}