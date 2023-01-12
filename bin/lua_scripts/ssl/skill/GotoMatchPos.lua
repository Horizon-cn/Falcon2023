function GotoMatchPos(task)
	local mpos
	local mdir
	local mflag = task.flag or 0
	local msender = task.sender or 0 -- 只执行一次
	local mrole = task.srole or ""
	local macc = task.acc or 0
	local mmethod = task.method or 4

	matchPos = function()
		if type(task.pos) == "function" then
			mpos = task.pos()
		else
			mpos = task.pos
		end
		return mpos
	end
	
	execute = function(runner)
		if runner>=0 and runner < param.maxPlayer then
			if mrole ~= "" then
				if mrole == "multiBack" then -- multiBack不注册
					guardPos:setBackNum(runner, task.sender)
					msender = 0 -- 只是借用task.sender把index传进来，用完后清零
				else
					CRegisterRole(runner, mrole)
				end
			end
		else
			print("Error runner in GotoMatchPos", runner)
		end
		
		for rolename, num in pairs(gRoleNum) do
			if num == runner and IsRoleActive(rolename) then
				mpos = gRolePos[rolename]
				break
			end
		end

		if type(task.dir) == "function" then
			mdir = task.dir(runner)
		else
			mdir = task.dir
		end

		if type(task.sender) == "string" then
			msender = player.num(task.sender)
		end
		
		if mrole == "leftBack" or mrole == "rightBack" or mrole == "singleBack" 
			or mrole == "leftCenterBack" or mrole == "rightCenterBack" then
			if player.posX(runner) < -param.pitchLength/4 then
				macc = 650
			else
				macc = 550
			end

			if player.toOurGoalDist(runner) > param.penaltyDepth * 2 then
				mflag = bit:_and(mflag, bit:_not(flag.not_avoid_our_vehicle))
			end
		end

		if mmethod == 4 then
			return SmartGotoPos(runner, mpos:x(), mpos:y(), mdir, mflag, msender, macc)
		else
			return CGoCmuRush(runner, mpos:x(), mpos:y(), mdir, mflag, msender, macc)
		end
	end

	return execute, matchPos
end

gSkillTable.CreateSkill{
	name = "GotoMatchPos",
	execute = function (self)
		print("This is in skill"..self.name)
	end
}
