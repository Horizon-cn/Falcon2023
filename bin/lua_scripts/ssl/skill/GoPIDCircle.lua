function GoPIDCircle(task)
    
    execute = function(runner)
        return CGoPIDCircle(runner, task.pos:x(), task.pos:y(), task.rad, task.opt)
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
	name = "GoPIDCircle",
	execute = function (self)
		print("This is in skill"..self.name)
	end
}