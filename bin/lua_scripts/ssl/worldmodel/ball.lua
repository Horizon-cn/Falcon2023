module(..., package.seeall)

function pos()
	return vision:Ball():Pos()
end

function posX()
	return vision:Ball():X()
end

function posY()
	return vision:Ball():Y()
end

function vel()
	return vision:Ball():Vel()
end

function velX()
	return vision:Ball():VelX()
end

function velY()
	return vision:Ball():VelY()
end

function velDir()
	return vision:Ball():Vel():dir()
end

function velMod()
	return vision:Ball():Vel():mod()
end

function valid()
	return vision:Ball():Valid()
end

function toPlayerDir(role)
	return (player.pos(role)- pos()):dir()
end

function toEnemyDir(role)
	return (enemy.pos(role)-pos()):dir()
end

-- role为接球车
function toPlayerHeadDir(recver)
	return function (passer)
		local tmpPlayerHead = player.pos(recver) + Utils.Polar2Vector(10, player.dir(recver))
		return (tmpPlayerHead - player.pos(passer)):dir()
	end
end

function toPlayerHeadDist(role)
	local tmpPlayerHead = player.pos(role) + Utils.Polar2Vector(10, player.dir(role))
	return (ball.pos() - tmpPlayerHead):mod()
end

function toPlayerDist(role)
	return (player.pos(role)- pos()):mod()
end

function toEnemyDist(role)
	return (enemy.pos(role) - pos()):mod()
end

function toTheirGoalDist()
	return pos():dist(CGeoPoint:new_local(param.pitchLength / 2.0, 0))
end

function toTheirGoalDir()
	return (CGeoPoint:new_local(param.pitchLength / 2.0,0) - ball.pos()):dir()
end

function toOurGoalDist()
	return pos():dist(CGeoPoint:new_local(-param.pitchLength / 2.0, 0))
end

function toOurGoalPostDistSum()
	local dist1 = pos():dist(CGeoPoint:new_local(-param.pitchLength / 2.0, -param.goalWidth / 2.0))
	local dist2 = pos():dist(CGeoPoint:new_local(-param.pitchLength / 2.0, param.goalWidth / 2.0))
    return (dist1 + dist2)
end

function toOurGoalDir()
	return (CGeoPoint:new_local(-param.pitchLength / 2.0, 0) - ball.pos()):dir()
end

function toPointDir(p)
	return function ()
		return (p - pos()):dir()
	end
end

function toPointDist(p)
	return pos():dist(p)
end

function antiY()
	if posY() > 0 then
		return -1
	else
		return 1
	end
end

function syntY()
	return -1*antiY()
end

function antiYPos(p)
	return function ()
		if type(p) == "function" then
			return CGeoPoint(p():x(), antiY()*p():y())
		else
			return CGeoPoint(p:x(), antiY()*p:y())
		end
	end
end

function syntYPos(p)
	return function ()
		return CGeoPoint(p:x(), syntY()*p:y())
	end
end

function toFuncDir(f)
	return function ()
		return (f() - pos()):dir()
	end
end

function antiYDir(p)
	return function ()
		if type(p) == "userdata" then
			return (antiYPos(p)() - pos()):dir()
		elseif type(p) == "number" then
			return ball.antiY()*p
		elseif type(p) == "function" then
			return (antiYPos(p())() - pos()):dir()
		end
	end
end

function syntYDir(p)
	return function ()
		if type(p) == "userdata" then
			return (syntYPos(p)() - pos()):dir()
		elseif type(p) == "number" then
			return ball.syntY()*p
		end
	end
end

function toBestEnemyDist()
	local enemyNum = defenceInfoNew:getBestBallChaser()
	if Utils.PlayerNumValid(enemyNum) then
		return toEnemyDist(enemyNum)
	else
		return 1000
	end
end

function enemyDistMinusPlayerDist(role)
	return toBestEnemyDist() - toPlayerDist(role)
end

function goRush()
	return function ()
		-- changed to Brazil by zhyaic
		return CGeoPoint:new_local(refPosX() - 100, 150 * refAntiY())
	end
end

function backDir(p, anti)
	return function ()
		local idir
		if type(p) == "function" then
			idir = p()
		elseif type(p) == "number" then
			idir = p
		elseif type(p) == "userdata" then
			if anti == false then
				idir = Utils.Normalize((p - ball.pos()):dir())
			else
				local targetP = CGeoPoint:new_local(p:x(), ball.antiY()*p:y())
				idir = Utils.Normalize((targetP - ball.pos()):dir())
			end
		elseif type(p) == "string" then
			idir = Utils.Normalize((player.pos(p) - ball.pos()):dir())
		end

		if type(idir) == "userdata" then
			if anti == false then
				idir = Utils.Normalize((idir - ball.pos()):dir())
			else
				local temP = CGeoPoint:new_local(idir:x(), ball.antiY()*idir:y())
				idir = Utils.Normalize((temP - ball.pos()):dir())
			end
		end
		return idir
	end
end

-- p为朝向点，d为纵向偏移量，s为横向偏移量
function backPos(p, d, s, anti)
	return function ()
		local idir = backDir(p, anti)()
		if d == nil then
			d = 18
		end

		local ipos
		if s == nil then
			s = 0
		end
		local shiftVec = Utils.Polar2Vector(s, idir):rotate(syntY()*math.pi/2)
		local ipos = ball.pos() + shiftVec + Utils.Polar2Vector(d, Utils.Normalize(idir + math.pi))
		return ipos
	end
end

-- p为面朝的点, d为纵向偏移，s为横向偏移
function jamPos(p, d, s)
	return function ()
		if d == nil then
			d = 55
		end

		if s == nil then
			s = 0
		end

		local targetP = CGeoPoint:new_local(p:x(), p:y()*ball.antiY())
		local faceDir = (targetP - ball.pos()):dir()
		local shiftVec = Utils.Polar2Vector(s, faceDir):rotate(antiY()*math.pi/2)
		return ball.pos() + Utils.Polar2Vector(d, faceDir) + shiftVec
	end
end

-- (卡对方的防开球车) 球在左边半场时，球与对方球门连线的左边; 球在右边半场时，球与对方球门连线的右边
function jaminner(dist)
	return function ()
		local ball = ball.pos()
		local gate = CGeoPoint:new_local(param.pitchLength / 2, 0)
		local balltoGate = gate - ball
		local d = dist and dist or 58
		local jamVec = balltoGate:rotate(antiY() * 0.39) / balltoGate:mod() * d
		return ball + jamVec
	end
end

function jamouter(dist)
	return function ()
		local ball = ball.pos()
		local gate = CGeoPoint:new_local(param.pitchLength / 2, 0)
		local balltoGate = gate - ball
		local d = dist and dist or 58
		local jamVec = balltoGate:rotate(antiY() * -0.39) / balltoGate:mod() * d
		return ball + jamVec
	end
end

gRefMsg = {
	-- 上一次定位球的Cycle
	lastCycle = 0,
	-- 本次定位球开始时球的X位置
	ballX     = 0,
	-- 本次定位球开始时球的Y位置
	ballY     = 0,
	-- 本次定位球的antiY参数
	antiY     = 1,
	-- 本次定位球是不是我方的球
	isOurBall = false
}

-- 当有裁判盒信息切换时进行更新的信息
function updateRefMsg()
	if (vision:Cycle() - gRefMsg.lastCycle) > 6 then
		gRefMsg.ballX = posX()
		gRefMsg.ballY = posY()
		gRefMsg.antiY = antiY()
		gRefMsg.isOurBall = world:IsOurBallByAutoReferee()
	else
		if math.abs(gRefMsg.ballX - posX()) > 10 then
			gRefMsg.ballX = posX()
		end
		if math.abs(gRefMsg.ballY - posY()) > 10 then
			gRefMsg.ballY = posY()
		end
		gRefMsg.antiY = antiY()
	end

	gRefMsg.lastCycle = vision:Cycle()
end

function refPosX()
	return gRefMsg.ballX
end

-- 在裁判盒时使用的bally
function refPosY()
	return gRefMsg.ballY
end

function refAntiY()
	return gRefMsg.antiY
end
-- 在定位球中使用的反向点
function refAntiYPos(p)
	return function ()
		return CGeoPoint(p:x(), gRefMsg.antiY*p:y())
	end
end

-- 在定位球中使用的反向点
function refSyntYPos(p)
	return function ()
		return CGeoPoint(p:x(), -1*gRefMsg.antiY*p:y())
	end
end

-- 在定位球中使用的反向朝向
function refAntiYDir(p)
	return function ()
		return gRefMsg.antiY*p
	end
end

-- 在定位球中使用的同向朝向
function refSyntYDir(p)
	return function ()
		if type(p) == "function" then
			return -1*gRefMsg.antiY*p()
		else
			return -1*gRefMsg.antiY*p
		end
	end
end

-- 是否我方开定位球
function refIsOurBall(p)
	return gRefMsg.isOurBall
end

function supportPassPos(num)
	return function ()
		local passPos = bestAlg:getBestPointFromArea(num)
		return passPos
	end
end

-- 以下四个函数通过WorldModel调用NormalPlayUtils，现改为直接调用gpuBestAlgThread，但是原路径仍未删除，建议中国赛后整理lua到C++接口
function LWPassPos()
	return function ()
		-- local passPos1=CGeoPoint:new_local(100,-100)
		-- local passPos2=CGeoPoint:new_local(100,100)
		-- local passPos3=CGeoPoint:new_local(-100,-100)
		-- local passPos4=CGeoPoint:new_local(-100,100)
		-- world:generatePassPoint(passPos1,passPos2,passPos3,passPos4)
		local passPos = bestAlg:getBestPointFromArea(0)
		return passPos
	end
end

function MWPassPos()
	return function ()
		local passPos = bestAlg:getBestPointFromArea(1)
		return passPos
	end
end

function RWPassPos()
	return function ()
		-- local passPos1=CGeoPoint:new_local(100,-100)
		-- local passPos2=CGeoPoint:new_local(100,100)
		-- local passPos3=CGeoPoint:new_local(-100,-100)
		-- local passPos4=CGeoPoint:new_local(-100,100)
		-- world:generatePassPoint(passPos1,passPos2,passPos3,passPos4)
		local passPos = bestAlg:getBestPointFromArea(2)
		return passPos
	end
end

function LMPassPos()
	return function ()
		-- local passPos1=CGeoPoint:new_local(100,-100)
		-- local passPos2=CGeoPoint:new_local(100,100)
		-- local passPos3=CGeoPoint:new_local(-100,-100)
		-- local passPos4=CGeoPoint:new_local(-100,100)
		-- world:generatePassPoint(passPos1,passPos2,passPos3,passPos4)
		local passPos = bestAlg:getBestPointFromArea(3)
		return passPos
	end
end

function MMPassPos()
	return function ()
		-- local passPos1=CGeoPoint:new_local(100,-100)
		-- local passPos2=CGeoPoint:new_local(100,100)
		-- local passPos3=CGeoPoint:new_local(-100,-100)
		-- local passPos4=CGeoPoint:new_local(-100,100)
		-- world:generatePassPoint(passPos1,passPos2,passPos3,passPos4)
		local passPos = bestAlg:getBestPointFromArea(4)
		return passPos
	end
end

function RMPassPos()
	return function ()
		-- local passPos1=CGeoPoint:new_local(100,-100)
		-- local passPos2=CGeoPoint:new_local(100,100)
		-- local passPos3=CGeoPoint:new_local(-100,-100)
		-- local passPos4=CGeoPoint:new_local(-100,100)
		-- world:generatePassPoint(passPos1,passPos2,passPos3,passPos4)
		local passPos = bestAlg:getBestPointFromArea(5)
		return passPos
	end
end


-- 球是否朝着某个角色运动
function isMovingTo(role)
	if ball.valid() and ball.velMod() > 1 and math.abs(Utils.Normalize(ball.velDir() - ball.toPlayerDir(role))) < math.pi / 9 then
		return true
	end
	return false
end

function placementPos()
    return vision:getBallPlacementPosition()
end


function readyplacementPos() 
        return function ()
               --放球点在左上
               if ball.posX() > ball.placementPos():x() and  ball.posY() >ball.placementPos():y() and ball.posX()-ball.placementPos():x()> ball.posY()-ball.placementPos():y()  then
		         if ball.placementPos():y()+250<450 then
		           return CGeoPoint(ball.placementPos():x(), ball.placementPos():y()+250)
		         else 
		           return CGeoPoint(ball.placementPos():x(), ball.placementPos():y()-250)
		         end
               end
               if ball.posX() > ball.placementPos():x() and  ball.posY() >ball.placementPos():y() and ball.posX()-ball.placementPos():x()<= ball.posY()-ball.placementPos():y()  then
		         if ball.placementPos():x()+250<600 then
		           return CGeoPoint(ball.placementPos():x()+250, ball.placementPos():y())
		         else
		           return CGeoPoint(ball.placementPos():x()-250, ball.placementPos():y())
		         end
               end
               --放球点在右上
               if ball.posX() <= ball.placementPos():x() and  ball.posY() >ball.placementPos():y() and ball.placementPos():x()-ball.posX()> ball.posY()-ball.placementPos():y()  then
		          if ball.placementPos():y()+250<450 then 
		            return CGeoPoint(ball.placementPos():x(), ball.placementPos():y()+250)
		          else 
		          	return CGeoPoint(ball.placementPos():x(), ball.placementPos():y()-250)
		          end
               end
               if ball.posX() <= ball.placementPos():x() and  ball.posY() >ball.placementPos():y() and ball.placementPos():x()-ball.posX()<= ball.posY()-ball.placementPos():y()  then
		          if ball.placementPos():x()-250>-600 then
		            return CGeoPoint(ball.placementPos():x()-250, ball.placementPos():y())
		          else
		          	return CGeoPoint(ball.placementPos():x()+250, ball.placementPos():y())
		          end
               end
               --放球点在左下
               if ball.posX() > ball.placementPos():x() and  ball.posY() <=ball.placementPos():y() and ball.posX()-ball.placementPos():x()> ball.placementPos():y()-ball.posY()  then
		         if ball.placementPos():y()-250>-450 then 
		            return CGeoPoint(ball.placementPos():x(), ball.placementPos():y()-250)
		         else 
		         	return CGeoPoint(ball.placementPos():x(), ball.placementPos():y()+250)
		         end
               end
               if ball.posX() > ball.placementPos():x() and  ball.posY() <=ball.placementPos():y() and ball.posX()-ball.placementPos():x()<= ball.placementPos():y()-ball.posY()  then
		         if ball.placementPos():x()+250<600 then
		            return CGeoPoint(ball.placementPos():x()+250, ball.placementPos():y())
		         else
		         	return CGeoPoint(ball.placementPos():x()-250, ball.placementPos():y())
		         end
               end
               --放球点在右下
               if ball.posX() <= ball.placementPos():x() and  ball.posY() <=ball.placementPos():y() and ball.posX()-ball.placementPos():x()> ball.placementPos():y()-ball.posY()  then
		         if  ball.placementPos():y()-250>-450 then
 		           return CGeoPoint(ball.placementPos():x(), ball.placementPos():y()-250)
 		         else
 		           return CGeoPoint(ball.placementPos():x(), ball.placementPos():y()+250)
 		         end
               end
               if ball.posX() <= ball.placementPos():x() and  ball.posY() <=ball.placementPos():y() and ball.posX()-ball.placementPos():x()<= ball.placementPos():y()-ball.posY()  then
		         if ball.placementPos():x()-250>-600 then
		           return CGeoPoint(ball.placementPos():x()-250, ball.placementPos():y())
		         else
		           return CGeoPoint(ball.placementPos():x()+250, ball.placementPos():y())
		         end
               end
        end
end