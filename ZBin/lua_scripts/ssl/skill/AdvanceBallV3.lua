function AdvanceBallV3(task)
	local mpos
	local mflag     = task.flag or 0
	local mrole     = task.srole or ""
	local tandem = function ()
		return gRoleNum["Special"]
	end

	execute = function(runner)
		if runner >= 0 and runner < param.maxPlayer then
			if mrole ~= "" then
				CRegisterRole(runner, mrole)
			end
		else
			print("Error runner in AdvanceBall", runner)
		end
		local tandemNum    = tandem() and tandem() or 0
		return CAdvanceBallPass(runner, mflag, tandemNum)  --return CAdvanceBall(runner, mflag, tandemNum)-- return CAdvanceBallOld(runner, mflag)
		--return CAdvanceBall(runner, mflag, tandemNum)
	end

	matchPos = function()
		if type(task.pos) == "function" then
			mpos = task.pos()
		else
			mpos = task.pos
		end

		return mpos
	end

	return execute, matchPos
end

gSkillTable.CreateSkill{
	name = "AdvanceBallV3",
	execute = function (self)
		print("This is in skill"..self.name)
	end
}
