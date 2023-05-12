function JustKick(task)
	local mmode
	local mpower = task.power
	local mflag = task.flag

	-- ischipkick
	if task.mode=="kick" then
		mmode=0
	else
		mmode=1
	end

	execute = function(runner)
		return CJustKick(runner, mmode, mpower, mflag)
	end

	matchPos = function()
		return ball.pos()
	end

	return execute, matchPos
end

gSkillTable.CreateSkill{
	name = "JustKick",
	execute = function (self)
		print("This is in skill"..self.name)
	end
}
