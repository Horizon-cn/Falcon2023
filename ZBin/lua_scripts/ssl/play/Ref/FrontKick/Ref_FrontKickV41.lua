----------------------------------------------------------
-----             SRC lua             ------
-----   中场任意球，使用范围中线0~125   ------
-----          SCJ 2020/11/10 改      ------
-- 用在中场靠中间位置的定位球，主要要考虑到球的y值会在正负之前跳动

-- mjx  2020.11.12
local MAKE_POS_ORG    = CGeoPoint:new_local(200, -250)
local RIGHT_POS   = ball.refSyntYPos(CGeoPoint:new_local(330, 220))
local RIGHT_POS2  = ball.refSyntYPos(CGeoPoint:new_local(280, -250))
local MAKE_POS    = ball.refAntiYPos(MAKE_POS_ORG)
local READY_POS   = ball.refSyntYPos(CGeoPoint:new_local(70, -150))
--local SHOOT_POS   = ball.refSyntYPos(CGeoPoint:new_local(70, -150))
local MASK_POS    = ball.refSyntYPos(CGeoPoint:new_local(280, 180))
local SHOOT_POS2  = ball.refSyntYPos(CGeoPoint:new_local(280, -130))
local FAKE_POS    = ball.refSyntYPos(CGeoPoint:new_local(250,-250))
local GOAL_POS    = CGeoPoint:new_local(450,-15)
local ball_posY   = ball.posY()
local ball_posX   = ball.posX()
local SHOOT_POS   = pos.passForTouch(READY_POS)
local LEFT_BACK_POS = ball.refSyntYPos(CGeoPoint:new_local(0,270))
local RIGHT_BACK_POS = ball.refSyntYPos(CGeoPoint:new_local(0,-250))

-- local ANTIS = ANTI()
local ANTI = function ()
	if ball_posY < 0 then
		return 1
	elseif ball_posY >= 0 then 
		return -1
	end
end

gPlayTable.CreatePlay{

firstState = "getready",

["getready"] = {
	switch = function ()
		if bufcnt(player.toTargetDist("Leader")<40 and
			player.toTargetDist("Assister")<10, 3, 180) then
			return "chippass"
		end
	end,
	Assister = task.slowGetBall(SHOOT_POS()),
	Middle   = task.rightBack(),
	Special  = task.leftBack(),
	Leader 	 = task.goCmuRush(MAKE_POS, player.toBallDir, _, flag.avoid_stop_ball_circle),
	Defender = task.goCmuRush(READY_POS),
	Goalie   = task.goalie(),
	match    = "{AD}[LSM]"
},

["chippass"] = {
	switch = function ()
		-- if bufcnt( player.toBallDist("Assister") > 20, 10, 180)then
		if bufcnt(player.kickBall("Assister"), "fast", 180)then
			return "waitBall"
		end
	end,
	Assister = task.chipPass(SHOOT_POS() , 180),
	Middle   = task.rightBack(),
	Special  = task.leftBack(),
	Leader 	 = task.goCmuRush(MAKE_POS, player.toBallDir, _, flag.avoid_stop_ball_circle),
	Defender = task.goCmuRush(READY_POS),
	Goalie   = task.goalie(),
	match    = "{AD}{LSM}"
},

["waitBall"] = {
    switch = function ()
      if bufcnt(player.toPointDist("Defender", READY_POS) < 50, 40, 80) then
        return "gokick"
      end
    end,
    Assister = task.goCmuRush(FAKE_POS, _, _, flag.avoid_stop_ball_circle),
    Leader   = task.continue(),
    Special  = task.leftBack(),
    Middle   = task.rightBack(),
    Defender = task.goCmuRush(READY_POS),
    Goalie   = task.goalie(),
    match    = "{AD}{LSM}"
  },

["gokick"] = {
    switch = function ()
		if player.kickBall("Leader") then
			return "finish"
		elseif  bufcnt(true, 180) then
			return "exit"
		end
	end,
	Leader = task.defendMiddle(),
	Middle   = task.rightBack(),
	Defender  = task.chaseNew(),
	Special   = task.leftBack(),
	Assister = task.goCmuRush(LEFT_BACK_POS),
	Goalie   = task.goalie(),
	match    = "{AD}{LSM}"
},

name = "Ref_FrontKickV41",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}
