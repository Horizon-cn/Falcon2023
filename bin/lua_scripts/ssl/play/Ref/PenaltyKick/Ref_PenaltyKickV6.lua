local function dir__dead()
	local function dir_dead_inside(runner)
		return (CGeoPoint:new_local(600,50)-ball.pos()):dir()
	end
	return dir_dead_inside
end

gPlayTable.CreatePlay{

firstState = "init",

["init"] = {
	switch = function ()
		if bufcnt(ball.posX()<0, "fast", 50) then
			return "gotolong"
		end
	end,
	Goalie = task.goalie(),
	Leader = task.goCmuRush(CGeoPoint:new_local(-260,0),_,_,flag.allow_dss),
	Assister = task.goCmuRush(CGeoPoint:new_local(-260,100),_,_,flag.allow_dss),
	Middle = task.goCmuRush(CGeoPoint:new_local(-260,-100),_,_,flag.allow_dss),
    Special = task.goCmuRush(CGeoPoint:new_local(-260,50),_,_,flag.allow_dss),
	Defender = task.goCmuRush(CGeoPoint:new_local(-260,-50),_,_,flag.allow_dss),
	match = "[L][DS][AM]"
},

["gotolong"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Goalie") < 30 , 10 , 120) then
			return "templong"
		end
	end,
	Goalie  = task.goCmuRush(CGeoPoint:new_local(-200,0)),
	Leader = task.goCmuRush(CGeoPoint:new_local(-260,0),_,_,flag.allow_dss),
	Assister = task.goCmuRush(CGeoPoint:new_local(-260,100),_,_,flag.allow_dss),
	Middle = task.goCmuRush(CGeoPoint:new_local(-260,-100),_,_,flag.allow_dss),
    Special = task.goCmuRush(CGeoPoint:new_local(-260,50),_,_,flag.allow_dss),
	Defender = task.goCmuRush(CGeoPoint:new_local(-260,-50),_,_,flag.allow_dss),
	match = "[L][DS][AM]"
},

["templong"] = {
	switch = function ()
		if bufcnt(cond.isNormalStart()) then
			return "kick"
		end
	end,
	Goalie  = task.goCmuRush(CGeoPoint:new_local(-170,0)),
	Leader = task.goCmuRush(CGeoPoint:new_local(-260,0),_,_,flag.allow_dss),
	Assister = task.goCmuRush(CGeoPoint:new_local(-260,100),_,_,flag.allow_dss),
	Middle = task.goCmuRush(CGeoPoint:new_local(-260,-100),_,_,flag.allow_dss),
    Special = task.goCmuRush(CGeoPoint:new_local(-260,50),_,_,flag.allow_dss),
	Defender = task.goCmuRush(CGeoPoint:new_local(-260,-50),_,_,flag.allow_dss),
	match = "[L][DS][AM]"
},

["kick"] = {
	switch = function ()
		if ball.posX()>500 then
			return "exit"
		end
	end,
	Goalie  = task.penaltykick(),
	Leader = task.goCmuRush(CGeoPoint:new_local(-260,0),_,_,flag.allow_dss),
	Assister = task.goCmuRush(CGeoPoint:new_local(-260,100),_,_,flag.allow_dss),
	Middle = task.goCmuRush(CGeoPoint:new_local(-260,-100),_,_,flag.allow_dss),
    Special = task.goCmuRush(CGeoPoint:new_local(-260,50),_,_,flag.allow_dss),
	Defender = task.goCmuRush(CGeoPoint:new_local(-260,-50),_,_,flag.allow_dss),
	match = "[L][DS][AM]"
},

name = "Ref_PenaltyKickV1",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
