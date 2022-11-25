local ball_posY   = ball.posY()
local ball_posX   = ball.posX()
local READY_POS   = ball.antiYPos(CGeoPoint:new_local(70, 150))
local SHOOT_POS   = pos.passForTouch(READY_POS)

gPlayTable.CreatePlay{

firstState = "getready",

["getready"] = {
		switch = function ()
			if bufcnt(player.toTargetDist("Receiver")<40 and
				player.toTargetDist("Kicker")<10, 3, 180) then
				return "chippass"
			end
		end,
		Receiver = task.slowGetBall(SHOOT_POS()),
		Kicker = task.goCmuRush(READY_POS),
		match    = ""
},

["chippass"] = {
		switch = function ()
			if player.kickBall("Receiver") then
				return "receive"
			end
		end,
		Receiver = task.passToPos(READY_POS, 300),
		Kicker = task.goCmuRush(READY_POS),
		match    = ""
},

["receive"] = {
    switch = function ()
			if bufcnt(ball.toPlayerHeadDist("Kicker") < 10, "fast") then
				return "gokick"
			elseif  bufcnt(true, 1800) then
				return "exit"
			end
		end,
		Receiver = task.stop(),
		Kicker  = task.receivePass("Receiver"),
		match    = ""
},


["gokick"] = {
    switch = function ()
			if player.kickBall("Kicker") then
				return "finish"
			elseif  bufcnt(true, 1800) then
				return "exit"
			end
		end,
		Receiver = task.stop(),
		Kicker  = task.chaseNew(),
		match    = ""
},

name = "Test_ReceivePass",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
