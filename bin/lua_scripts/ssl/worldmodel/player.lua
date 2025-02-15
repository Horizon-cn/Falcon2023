module(..., package.seeall)

function instance(role)
	local realIns
	if type(role) == "string" then
		realIns = vision:OurPlayer(gRoleNum[role])
	elseif type(role) == "number" then
--	and	role >= 1 and role <= param.maxPlayer then
		realIns = vision:OurPlayer(role)
	else
		print("Invalid role in player.instance!!!")
	end
	return realIns
end

function num(role)
	local retNum
	if type(role) == "string" then
		retNum = gRoleNum[role]
	elseif type(role) == "number" then
		retNum = role
	else
		print("Invalid role in player.instance!!!")
	end
	return retNum
end

function pos(role)
	return instance(role):Pos()
end

function posX(role)
	return instance(role):X()
end

function posY(role)
	return instance(role):Y()
end

function dir(role)
	return instance(role):Dir()
end

function vel(role)
	return instance(role):Vel()
end

function velDir(role)
	return vel(role):dir()
end

function velMod(role)
	return vel(role):mod()
end

function rotVel(role)
	return instance(role):RotVel()
end

function valid(role)
	return instance(role):Valid()
end

function toBallDist(role)
	return pos(role):dist(ball.pos())
end

function toBallDir(role)
	return (ball.pos() - pos(role)):dir()
end

function backBallDir(role)
	return (pos(role) - ball.pos()):dir()
end

function toTheirGoalDist(role)
	return pos(role):dist(CGeoPoint:new_local(param.pitchLength / 2.0, 0))
end

function toOurGoalDist(role)
	return pos(role):dist(CGeoPoint:new_local(-param.pitchLength / 2.0, 0))
end

function toTheirGoalDir(role)
	return (CGeoPoint:new_local(param.pitchLength / 2.0, 0) - pos(role)):dir()
end

function toPlayerDir(role1, role2)
	if role2 == nil then
		return function(role2)
			return (player.pos(role1) - player.pos(role2)):dir()
		end
	else
		return (player.pos(role2) - player.pos(role1)):dir()
	end
end

function toPlayerHeadDir(role1, role2)
	if role2 == nil then
		return function(role2)
			local tmpPlayerHead = player.pos(role1) + Utils.Polar2Vector(8, player.dir(role1))
			return (tmpPlayerHead - player.pos(role2)):dir()
		end
	else
		local tmpPlayerHead = player.pos(role2) + Utils.Polar2Vector(8, player.dir(role2))
		return (tmpPlayerHead - player.pos(role1)):dir()
	end
end

function toPlayerDist(role1, role2)
	if role2 == nil then
		return function(role2)
			return (player.pos(role1) - player.pos(role2)):mod()
		end
	else
		return (player.pos(role2) - player.pos(role1)):mod()
	end
end

function toTargetDist(role)
	return player.pos(role):dist(gRolePos[role])
end

function toTargetDir(role)
	return (gRolePos[role] - player.pos(role)):dir()
end
--need to modify
function toTheirPenaltyDist(role)
	local tmpToGoalDist = (CGeoPoint:new_local(param.pitchLength/2.0,0) - player.pos(role)):mod()
	return tmpToGoalDist - 80
end

function toPointDist(role, p)
	local pos
	if type(p) == "function" then
		pos = p()
	else
		pos = p
	end
	return player.pos(role):dist(pos)
end

-- 用在冲球时求出传球点后面的一个点
function backShootPos(p)
	local tmpShootDir = (p - CGeoPoint:new_local(param.pitchLength/2.0,0)):dir()
	return p + Utils.Polar2Vector(9, tmpShootDir)
end

function toPointDir(p, role) -- todo 赛后改

	return function ()
		local idir
		if type(p) == "function" then
			idir = p()
		elseif type(p) == "number" then
			idir = p
		elseif type(p) == "userdata" then
			idir = Utils.Normalize((p - ball.pos()):dir())
		elseif type(p) == "string" then
			idir = Utils.Normalize((player.pos(p) - ball.pos()):dir())
		end

		if type(idir) == "userdata" then
			idir = Utils.Normalize((idir - ball.pos()):dir())
		end
		return idir
	end
end

function kickBall(role)
	return world:IsBallKicked(num(role))
end

-- role1为传球车
function toShootOrRobot(role1)
	return function(role2)
		local shootDir = ( CGeoPoint:new_local(param.pitchLength / 2.0, 0) - pos(role2) ):dir()
		local faceDir
		if toBallDist(role1) > 50 then
			faceDir = (ball.pos() - pos(role2)):dir()
		else
			faceDir = (pos(role1) - pos(role2)):dir()
		end
		return faceDir
		--if math.abs(Utils.Normalize(shootDir - faceDir)) > math.pi * 65 / 180 then
		--	return faceDir
		--else
		--	return shootDir
		--end
	end
end

function waitAdvancePos(role)
	return function (role2)
		local ballPos=CGeoPoint:new_local(ball.posX(),ball.posY())
		if NormalPlayUtils.isEnemyBlockShootLine(ballPos,ball.toTheirGoalDir(),50) then
			return firstPassPos(role)
		else

			return ballPos
		end

	end
end

function passPos(role)
	local lastRobotX   = 0
	local lastCycle    = 0
	local lastRobotNum = 0
	local lastPos      = CGeoPoint:new_local(0,0)

	return function ()
		local factor
		if math.abs(lastRobotX - posX(role)) > 50 or
		 	vision:Cycle() - lastCycle > 6 or
		 	num(role) ~= lastRobotNum then
			local factor
			local passX
			local passY
			if posY(role) > 0 then
				factor = -1
			else
				factor = 1
			end
			passY = 150*param.widthRatio*factor
			if posX(role) <= 0 then
				passX = 50*param.lengthRatio
			elseif posX(role) > 0 and posX(role) < 150*param.lengthRatio then
				passX = posX(role) + 50*param.lengthRatio
			else
				passX = 200*param.lengthRatio
			end
			bestAlg:setSendPoint(pos(role))
			local leftUpP = CGeoPoint:new_local(passX+50*param.lengthRatio, passY-30*param.widthRatio)
			local rightDownP = CGeoPoint:new_local(passX-50*param.lengthRatio, passY+30*param.widthRatio)
			lastPos = bestAlg:getBestPoint(leftUpP, rightDownP, 9)
			lastRobotX = posX(role)
		end

		lastCycle = vision:Cycle()
		lastRobotNum = num(role)
		return lastPos
	end
end

function canBreak(role)
	for i=1,6 do
		if enemy.valid(i) then
			local breakSeg = CGeoSegment:new_local(player.pos(role), gRolePos[role])
			local projP = breakSeg:projection(enemy.pos(i))
			if breakSeg:IsPointOnLineOnSegment(projP) then
				if enemy.pos(i):dist(projP) < 40 then
					return false
				end
			end
		end
	end

	return true
end

function isMarked(role)
	local closestDist = 9999
	for i=1,6 do
		if enemy.valid(i) then
			local dir1 = player.toPointDir(CGeoPoint:new_local(param.pitchLength / 2.0, 0),role)
			local dirDiff = Utils.Normalize( dir1- player.toPointDir(enemy.pos(i),role))
			if math.abs(dirDiff) < math.pi/2 then
				local tmpDist = player.toPointDist(role,enemy.pos(i))
				if tmpDist < closestDist then
					closestDist = tmpDist
				end
			end
		end
	end

	if closestDist < 30 then
		return true
	end
	return false
end

function testPassPos(role)
	local factor
	return function ()
		if posX(role) > 0 then
			factor = -1
		else
			factor = 1
		end

		return CGeoPoint:new_local(150*factor, 0)
	end
end

function testPassPosNew(role)
	local factor
	return function ()
		if posY(role) > 0 then
			factor = -1
		else
			factor = 1
		end

		return CGeoPoint:new_local(-120, 120*factor)
	end
end

function testPassPosThree(role)
	local factor
	return function ()
		if posX(role) > 0 then
			return CGeoPoint:new_local(100, 0)
		end

		if posY(role) > 0 then
			factor = 1
		else
			factor = -1
		end

		return CGeoPoint:new_local(-50, 87*factor)
	end
end

function testPassPosHard(role)
	local factor
	return function ()
		if posX(role) > -100 and posY(role) > 0 then
			return CGeoPoint:new_local(-50, 87)
		end

		if posX(role) > -100 and posY(role) < 0 then
			return CGeoPoint:new_local(-50, -87)
		end

		if posY(role) > 0 then
			factor = 1
		else
			factor = -1
		end

		return CGeoPoint:new_local(-150, 87*factor)
	end
end

function canFlatPassTo(role1, role2)
	local p1 = player.pos(role1)
	local p2 = player.pos(role2)
	local seg = CGeoSegment:new_local(p1, p2)
	for i = 0, param.maxPlayer-1 do
		if enemy.valid(i) then
			local dist = seg:projection(enemy.pos(i)):dist(enemy.pos(i))
			local isprjon = seg:IsPointOnLineOnSegment(seg:projection(enemy.pos(i)))
			if dist < 15 and isprjon then
				return false
			end
		end
	end

	return true
end

-- d为前方的距离
function canDirectShoot(role1, d)
	if d == nil then
		d = 70
	end
	local p1 = player.pos(role1)
	local p2 = player.pos(role1) + Utils.Polar2Vector(d,player.dir(role1))
	local seg = CGeoSegment:new_local(p1, p2)
	for i = 0, param.maxPlayer-1 do
		if enemy.valid(i) then
			local dist = seg:projection(enemy.pos(i)):dist(enemy.pos(i))
			local isprjon = seg:IsPointOnLineOnSegment(seg:projection(enemy.pos(i)))
			if dist < 12 and isprjon then
				return false
			end
		end
	end

	return true
end

function canChipPassTo(role1, role2)
	local p1 = player.pos(role1)
	local p2 = player.pos(role2)
	for i = 0, param.maxPlayer-1 do
		if enemy.valid(i) then
			local dist1 = enemy.pos(i):dist(p1)
			local dist2 = enemy.pos(i):dist(p2)
			if dist1 < 30 or dist2 < 30 then
				return false
			end
		end
	end

	return true
end

------------------------------------------------------
function isBallPassed(role1,role2)
	local p1 = player.pos(role1)
	local p2 = player.pos(role2)
	local ptrDir = ( p2 - p1 ):dir()
	if (math.abs(Utils.Normalize(ball.velDir() - ptrDir)) < math.pi / 18) and
	   (ball.velMod() > 80) then
		return true
	else
		return false
	end
end

function isBallPassedNormalPlay(role1,role2)
	local passerDir = player.dir(role1)
	local p1 = player.pos(role1)
	local p2 = player.pos(role2)
	local ptrDir = ( p2 - p1 ):dir()
	if (math.abs(Utils.Normalize(ball.velDir() - ptrDir)) < math.pi / 18) and
	   (math.abs(Utils.Normalize(ball.velDir() - passerDir)) < math.pi / 10) and
	   (ball.velMod() > 160)  then
		return true
	else
		return false
	end
end

function passIntercept(role)
	local receiver = player.pos(role)
	local ptrDir = ( receiver - ball.pos()):dir()
	if ball.toPointDist(receiver) >50 then
		if math.abs(Utils.Normalize(ball.velDir() - ptrDir)) > math.pi / 10 or
			ball.velMod() < 120 then
			return true
		else
			return false
		end
	else
		return false
	end
end


function InfoControlled(role)
	local roleNum = player.num(role)
	--local isVisionBallControlled = bestPlayer:withBall() and (bestPlayer:getOurBestPlayer() == roleNum)
	--print("withBall: ", bestPlayer:withBall())
	--print("BestPlayer: ", bestPlayer:getOurBestPlayer() == roleNum)
	--if bestPlayer:getOurBestPlayer() == roleNum then
	--	return true
	--else
	--	return false
	--end
	return bestPlayer:getOurBestPlayer() == roleNum
end
------------------------------------------------------

-- p为传入的点
function antiYDir(p)
	return function (role)
		if type(p) == "userdata" then
			return (ball.antiYPos(p)() - player.pos(role)):dir()
		end
	end
end

function realNumExist(n)
	if player.valid(n) then
		return true
	end
	return false
end