function RunMultiPosVel(task)
 	local curIndex = 1
 	local ratio = 0.9
 	local mpos = {}
 	local mvel = {}
 	local mdir = {}
 	local mflag = task.flag or 0
 	local msender = task.sender
 	local mclose  = task.close
 	local mdist = task.dist or 20
 	local macc = task.acc or 0
 	local mrec    = task.rec or 0
 	local lastCycle = 0

	execute = function(runner)
		if player.pos(runner):dist(mpos[curIndex]) < mdist then
			local nextIndex = (curIndex) % table.getn(mpos) + 1
			if mclose == nil or mclose then
				curIndex = nextIndex
			else
				if nextIndex > curIndex then
				 	curIndex = nextIndex
				end 
			end
 		end
 		
 		if type(task.sender) == "string" then
 			msender = player.num(task.sender)
 		end

		lastCycle = vision:Cycle()
		-- return CGoCmuRush(runner, mpos[curIndex]:x(), mpos[curIndex]:y(), mdir[curIndex], mflag, msender, macc, mrec, 0, 0)
		return CGoCmuRush(runner, mpos[curIndex]:x(), mpos[curIndex]:y(), mdir[curIndex], mflag, msender, macc, mrec, mvel[curIndex]:x()/ratio, mvel[curIndex]:y()/ratio)
		-- return CGoCmuRush(runner, mpos[curIndex]:x(), mpos[curIndex]:y(), player.dir(runner), mflag, msender, macc, mrec, mvel[curIndex]:x()/ratio, mvel[curIndex]:y()/ratio)
	end

	matchPos = function()
		if vision:Cycle() - lastCycle > 6 then
			curIndex = 1
		end
		for i=1, table.getn(task.pos) do
			if type(task.pos[i]) == "function" then
				mpos[i] = task.pos[i]()
				mvel[i] = task.vel[i]()
				mdir[i] = task.dir[i]()
			else	
				mpos[i] = task.pos[i]
				mvel[i] = task.vel[i]
				mdir[i] = (task.vel[i]-CGeoPoint:new_local(0,0)):dir()
			end
		end
		return mpos[curIndex]
	end

	return execute, matchPos
 end

 gSkillTable.CreateSkill{
 	name = "RunMultiPosVel",
 	execute = function (self)
 		print("This is in skill"..self.name)
 	end
 }
