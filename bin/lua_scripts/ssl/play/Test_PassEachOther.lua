local record_file = "../data/BallModel/BallSpeed"..os.date("%Y-%m-%d-%H-%M-%S")..".txt"
local pass_cnt = 0
local min_player_num = 0
local anti_pos = 1
local init_x = 300 -- 565
local pass_power = function()
	local power = 650 - pass_cnt
	if power <= 0 then
		power = 0
	end
	return power
end
local getKickerNum = function()
	return pass_cnt % 2 + min_player_num
end
local getReceiverNum = function()
	return (pass_cnt + 1) % 2 + min_player_num
end
local getReceiverPos = function()
	if getReceiverNum() % 2 == 1 then
		return CGeoPoint:new_local(init_x, 415 * anti_pos) -- 定死，不随球移动
	elseif getReceiverNum() % 2 == 0 then
		return CGeoPoint:new_local(600 - init_x, -415 * anti_pos)
	end
end
local getEndNum1 = function()
	local EndNum = min_player_num - 1
	if EndNum < -1 then
		return -1
	else
		return EndNum
	end
end
local getEndNum2 = function()
	local EndNum = min_player_num - 2
	if EndNum < -1 then -- -2不合法
		return -1
	else
		return EndNum
	end
end
local End_Pos_1 = CGeoPoint:new_local(600, 20)
local End_Pos_2 = CGeoPoint:new_local(600, -20)
-- local SHOOT_POS = pos.passForTouch(getReceiverPos)
local MOVE_FLAG = flag.not_dodge_penalty + flag.dodge_ball

gPlayTable.CreatePlay{

firstState = "init",

["init"] = {
	switch = function ()
		if true then
			file = io.open(record_file, "a")
    		file:write("Kicker"," ","Pass_Power"," ","VelMod"," ","VelX"," ","VelY"," ","PosX"," ","PosY","\n")
			file:close()
			if ball.posY() > 0 then
				anti_pos = -1
			end
			if ball.posX() > 300 then 
				init_x = 600 - init_x
			end
			return "getready"
		end
	end,
	[getKickerNum] = task.stop(),
	[getReceiverNum] = task.stop(),
	match = ""
},

["getready"] = {
	switch = function ()
		if bufcnt(player.toTargetDist(getKickerNum()) < 40 and
			player.toTargetDist(getReceiverNum()) < 10, 3) then
			return "pass"
		end
	end,
	[getKickerNum] = task.getBall(getReceiverPos), -- SHOOT_POS -- 传入函数才能保证每一周期都更新
	[getReceiverNum] = task.goCmuRush(getReceiverPos, _, _, MOVE_FLAG),
	[getEndNum1] = task.goCmuRush(End_Pos_1, _, _, MOVE_FLAG), -- 退场
	[getEndNum2] = task.goCmuRush(End_Pos_2, _, _, MOVE_FLAG),
	match = ""
},

["pass"] = {
	switch = function ()
		if pass_power() == 0 then
			pass_cnt = 0
			min_player_num = min_player_num + 2
			return "getready"
		elseif player.kickBall(getKickerNum()) then
			return "receive"
		end
	end,
	[getKickerNum] = task.passToPos(getReceiverPos, pass_power),
	[getReceiverNum] = task.goCmuRush(getReceiverPos, _, _, MOVE_FLAG),
	match = ""
},

["receive"] = {
    switch = function ()
    	debugEngine:gui_debug_msg(CGeoPoint:new_local(300, 0), pass_power())
    	file = io.open(record_file, "a")
    	file:write(string.format("%d",getKickerNum())," ",pass_power()," ",ball.velMod()," ",ball.velX()," ",ball.velY()," ",ball.posX()," ",ball.posY(),"\n")
		file:close()
		if bufcnt(ball.toPlayerHeadDist(getReceiverNum()) < 10, "fast") then
			pass_cnt = pass_cnt + 1
			return "getready"
		end
	end,
	[getKickerNum] = task.stop(),
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
