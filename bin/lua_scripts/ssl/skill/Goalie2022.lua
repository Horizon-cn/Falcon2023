function Goalie2022(task)
	local mmode=task.mode
	local mflag = task.flag or 0

	local mpenalty=false
	if mmode=="penalty" then
		mpenalty=true
	elseif mmode~=nil then
		print('Error in Goalie2022: mode param error')
	end

	execute = function(runner)
		return CGoalie2022(runner, mpenalty, mflag)
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
