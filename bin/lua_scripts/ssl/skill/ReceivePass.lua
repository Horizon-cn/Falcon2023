function ReceivePass(task)
	local mdir
	local mflag = task.flag or 0
	local mmatch_p = task.match_p
	
	execute = function(runner)
		if type(task.dir) == "function" then
			mdir = task.dir(runner)
		else
			mdir = task.dir
		end
		return CReceivePass(runner, mdir, mflag)
	end

	matchPos = function()
		if mmatch_p then
			if type(mmatch_p) == "function" then
				mmatch_p= mmatch_p()
			end
			return mmatch_p
		else
			return pos.playerBest()
		end
	end

	return execute, matchPos
end

gSkillTable.CreateSkill{
	name = "ReceivePass",
	execute = function (self)
		print("This is in skill"..self.name)
	end
}
