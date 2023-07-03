local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling

local SwitchBallArea = function()
		if (ball.posY()<-220 or ball.posY()>220) and ball.posX()<-200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return "HardAttack_8"
			else 
				return "MultiDefend_8"
			end	
		elseif ball.posY()>-220 and ball.posY()<220 and ball.posX()<-200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return "MiddleAttack_8"
			else 
				return "MultiDefend_8"
			end
		elseif ball.posX()>-200 and ball.posX()<200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return "MiddleAttack_8"
			else 
				return "MiddleDefendBalance_8"
			end
		elseif ball.posX()>200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return "MultiAttack_8"
			else 
				return "MiddleAttack_8"
			end
		else
			return "MiddleDefendBalance_8"
		end
	
	end


gPlayTable.CreatePlay{

firstState = "MiddleAttack_8",
--defendhead防守圆角  
--defendkick球门与持球人的连线
--a->p->s 优先级

--可用于危险紧急防守或边线防守
--先2multiBack 1advance 1defendhead 1markingfront 再1multiBack 可以换1defendkick
["MultiDefend_8"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.multiBack(3,1),
    Middle = task.multiBack(3,2),
    Special = task.multiBack(3,3),
	Defender = task.defendHead(),
	Crosser  = task.markingFront("First"),
	Breaker  = task.defendKick(),
	Goalie = task.goalieNew(),
    match = "[L][AM][D][C][S][B]"
},

--可用于前场进攻
["MultiAttack_8"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
    Middle = task.markingFront("First"),
    Breaker  = task.protectBall(),
    Special = task.multiBack(3,1),
	Defender = task.rightBack(),
	Crosser  = task.leftBack(),	
	Goalie = task.goalieNew(),
    match = "[L][B][DC][S][M][A]"
},

--可用于中场半攻半防
["MiddleDefendBalance_8"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
    Middle = task.protectBall(), 
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  = task.multiBack(3,2),	
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DCB][M][S][A]"
},

--中前进攻
["MiddleAttack_8"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"),
    Middle =  task.protectBall(), 
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  = task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DCB][A][S][M]"
},

--适用于我方拿到球但接近我方禁区
["HardAttack_8"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"), 
    Middle = task.defendHead(), --task.marking("First"),
    Special = task.defendKick(),
	Defender = task.multiBack(3,1),
	Crosser  =  task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DCB][A][S][M]"
},

name = "Test_play8_NotFoul",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}