function FetchBall(task)
	local mpos = task.target
	local mdir
	local kickPower = 1200

	execute = function(runner)
		if type(task.kickpower) == "function" then
        	kickPower = task.kickpower(runner)
    	else
        	kickPower = task.kickpower
    	end
    	if type(task.dir) == "function" then
			mdir = task.dir(runner)
		else
			mdir = task.dir
		end
		return CFetchBall(runner, mpos:x(), mpos:y(), kickPower, mdir)
	end

	matchPos = function()
		return ball.pos()
	end

	return execute, matchPos
end

gSkillTable.CreateSkill{
	name = "FetchBall",
	execute = function (self)
		print("This is in skill"..self.name)
	end
}