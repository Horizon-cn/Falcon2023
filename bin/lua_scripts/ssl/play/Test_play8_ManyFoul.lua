local ALL_AVOID = flag.dodge_ball + flag.avoid_stop_ball_circle + flag.avoid_shoot_line
local ALL_NOT_AVOID = flag.not_avoid_their_vehicle + flag.not_avoid_our_vehicle + flag.not_dodge_penalty
local FLAG = ALL_AVOID + flag.dribbling
local SwitchBallArea = function()
		if (ball.posY()<-220 or ball.posY()>220) and ball.posX()<-200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return "HardAttack_lessthan7"
			else 
				return "MultiDefend_lessthan7"
			end	
		elseif ball.posY()>-220 and ball.posY()<220 and ball.posX()<-200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return "MiddleAttack_lessthan7"
			else 
				return "MultiDefend_lessthan7"
			end
		elseif ball.posX()>-200 and ball.posX()<200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return "MiddleAttack_lessthan7"
			else 
				return "MiddleDefendBalance_lessthan7"
			end
		elseif ball.posX()>200 then
			ballStatus=world:getBallStatus(vision:Cycle(),gRoleNum["Leader"])
			if ballStatus == "OurBall" then
				return "MultiAttack_lessthan7"
			else 
				return "MiddleAttack_lessthan7"
			end
		else
			return "MiddleDefendBalance_lessthan7"
		end	
	end
gPlayTable.CreatePlay{

firstState = "MiddleAttack_lessthan7",
--defendhead防守圆角  
--defendkick球门与持球人的连线
--a->p->s 优先级

--可用于危险紧急防守或边线防守
--先2multiBack 1advance 1defendhead 1markingfront 再1multiBack 可以换1defendkick
["MultiDefend_lessthan7"] = {
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
["MultiAttack_lessthan7"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
    Middle = task.markingFront("First"),
    Breaker  = task.support("Leader",1),
    Special = task.multiBack(3,1),
	Defender = task.rightBack(),
	Crosser  = task.leftBack(),
	Goalie = task.goalieNew(),
    match = "[L][DC][S][M][AB]"
},

--可用于中场半攻半防
["MiddleDefendBalance_lessthan7"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.support("Leader",0),
    Middle = task.defendHead(),
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  = task.multiBack(3,2),	
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DCB][M][S][A]"
},

--中前进攻
["MiddleAttack_lessthan7"] = {
	switch = SwitchBallArea,
	Leader = task.advance(),
	Assister = task.goMWPassPos("Leader"),
    Middle = task.defendHead(), 
    Special = task.markingFront("First"),
	Defender = task.multiBack(3,1),
	Crosser  = task.multiBack(3,2),
	Breaker  = task.multiBack(3,3),
	Goalie = task.goalieNew(),
    match = "[L][DCB][A][M][S]"
},

--适用于我方拿到球但接近我方禁区
["HardAttack_lessthan7"] = {
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


name = "Test_play8_ManyFoul",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}