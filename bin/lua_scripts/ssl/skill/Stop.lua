function Stop(task)	
	execute = function(runner)
		return CStopRobot(runner)
	end

	matchPos = function()
		return CGeoPoint:new_local(0,0)
	end

	return execute, matchPos
end

gSkillTable.CreateSkill{
	name = "Stop"
}
