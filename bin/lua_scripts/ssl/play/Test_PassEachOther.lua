local record_file = "../data/BallModel/BallSpeed"..os.date("%Y-%m-%d-%H-%M-%S")..".txt"
local isRecord = false
local pass_cnt = 0
local anti_pos = 1
local init_x = 350 -- 565 -- 300
local max_speed = 25 -- 标定的时候0~127，测试球速时意义为预期踢出的球速(cm/s)
local getKickerNum = function()
	if pass_cnt % 2 == 0 then
		return "Goalie"
	else
		return "Receiver"
	end
end
local getReceiverNum = function()
	if pass_cnt % 2 == 1 then
		return "Goalie"
	else
		return "Receiver"
	end
end
local pass_power = function()
	local temp1, temp2 = math.modf(pass_cnt / 2) -- 每个力度踢一次
	local power = max_speed - temp1
	if power <= 0 then
		power = 0
	end
	return power
end
local getReceiverPos = function()
	if pass_cnt % 2 == 0 then -- 415
		return CGeoPoint:new_local(init_x, 220 * anti_pos) -- 定死，不随球移动
	elseif pass_cnt % 2 == 1 then
		return CGeoPoint:new_local(init_x, -220 * anti_pos)
	end
end
local getKickerPos = function()
	local pos = getReceiverPos()
	return CGeoPoint:new_local(pos:x(), -pos:y()) -- param.pitchLength/2 - 
end
local receive_dir = function(num)
	return (player.pos(gRoleNum[getKickerNum()]) - player.pos(num)):dir()
end
local kick_dir = function(num)
	return (player.pos(gRoleNum[getReceiverNum()]) - player.pos(num)):dir()
end
-- local SHOOT_POS = pos.passForTouch(getReceiverPos)
local MOVE_FLAG = flag.not_dodge_penalty + flag.dodge_ball

gPlayTable.CreatePlay{

firstState = "init",

["init"] = {
	switch = function ()
		if isRecord then
			file = io.open(record_file, "a")
    		file:write("Kicker"," ","Pass_Power"," ","VelMod"," ","VelX"," ","VelY"," ","PosX"," ","PosY","\n")
			file:close()		
		end
		if ball.posY() > 0 then
			anti_pos = -1
		end
		if ball.posX() > 0 then 
			init_x = -init_x
		end	
		return "getready"
	end,
	[getKickerNum] = task.stop(),
	[getReceiverNum] = task.stop(),
	match = ""
},

["getready"] = {
	switch = function ()
		if bufcnt(player.toTargetDist(getReceiverNum()) < 10 and world:getBallPossession(true, gRoleNum[getKickerNum()]) > 0.3, 3) then
			return "pass"
		end
	end,
	[getKickerNum] = task.staticGetBall(getReceiverPos), -- SHOOT_POS -- 传入函数才能保证每一周期都更新
	[getReceiverNum] = task.goCmuRush(getReceiverPos, receive_dir, _, MOVE_FLAG),
	match = ""
},

["pass"] = {
	switch = function ()
		if pass_power() == 0 then
			pass_cnt = 0
			return "getready"
		elseif player.kickBall(getKickerNum()) then
			return "receive"
		end
	end,
	[getKickerNum] = task.passToPos(getReceiverPos, pass_power),
	[getReceiverNum] = task.goCmuRush(getReceiverPos, receive_dir, _, MOVE_FLAG),
	match = ""
},

["receive"] = {
    switch = function ()
    	debugEngine:gui_debug_msg(CGeoPoint:new_local(param.pitchLength/4, 0), pass_power())
    	if isRecord then
    		file = io.open(record_file, "a")
    		file:write(string.format("%d",getKickerNum())," ",pass_power()," ",ball.velMod()," ",ball.velX()," ",ball.velY()," ",ball.posX()," ",ball.posY(),"\n")
			file:close()
		end
		if bufcnt(ball.toPlayerHeadDist(getReceiverNum()) < 5, "fast") then
			pass_cnt = pass_cnt + 1
			return "getready"
		end
	end,
	[getKickerNum] = task.goCmuRush(getKickerPos, kick_dir, _, MOVE_FLAG),
	[getReceiverNum] = task.receive(ball.pos()),
	match = ""
},

name = "Test_PassEachOther",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
