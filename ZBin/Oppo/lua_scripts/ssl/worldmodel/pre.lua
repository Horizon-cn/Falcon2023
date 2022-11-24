module(..., package.seeall)

function specified(p)
	return function ()
		return p * math.pi / 180.0
	end
end

function high()
	return 1 * math.pi / 180.0
end

function middlehigh()
	return 3 * math.pi / 180.0
end

function middle()
	return 5 * math.pi / 180.0
end

function low()
	return 7 * math.pi / 180.0
end

function fieldDefender()
	local angle_left = 0
	local angle_right = 0
	local NearGoalDist = -param.pitchLength/2+10
	local fraredCount = 0
	return function()
		if ball.posY() >= -param.goalWidth/2 and ball.posY() <= param.goalWidth/2 then
			if ball.posX()>NearGoalDist then
				angle_left = -math.pi/2
				angle_right = math.pi/2
			else
				angle_left = -math.pi/3
				angle_right = math.pi/3
			end
		elseif ball.posY() < -param.goalWidth/2 then
			angle_left = -math.pi*2/3
			angle_right = math.pi/3
		elseif ball.posY() > param.goalWidth/2 then
			angle_left = -math.pi/3
			angle_right = math.pi*2/3
		end
		return Utils.Normalize((angle_right - angle_left)/2)
	end
end














