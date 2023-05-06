function DribbleTurnKickV2(task)
	local mdir = task.dir
	local mpre = task.precision
	local mmode
	local mpower = task.power

	-- ischipkick
	if task.mode=="kick" then
		mmode=0
	else
		mmode=1
	end

	if type(mpower)=="function" then
		mpower=mpower()
	end

	execute = function(runner)
		if type(mdir)=="function" then
			mdir=mdir(runner)
		end
		return CDribbleTurnKickV2(runner, mdir, mpre, mmode, mpower)
	end

	matchPos = function()
		return ball.pos()
	end

	return execute, matchPos
end

gSkillTable.CreateSkill{
	name = "DribbleTurnKickV2",
	execute = function (self)
		print("This is in skill"..self.name)
	end
}
