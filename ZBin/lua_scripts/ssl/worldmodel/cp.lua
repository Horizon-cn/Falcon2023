module(..., package.seeall)

function specified(p)
	return function ()
		return p
	end
end

function full()
	return function ()
		return 550
	end
end


function touch()
	return function ()
		return 480
	end
end

function slight()
	return function ()
		return 180
	end
end

function middle()
	return function ()
		return 220
	end
end

function normal()
	return function ()
		return 240
	end
end

-- 纯闭包函数，这个函数只是用在开射门的条件中
-- role1 为接球车
function toPlayer(role1)
	return function()
		local dist = ball.toPlayerDist(role1) --player.toPlayerDist(role1, role2)
		return dist
	end
end

function toTarget(p)
	return function()
		local tmpP
		if type(p) == "function" then
			tmpP = p()
		elseif type(p) == "userdata" then
			tmpP = p
		end

		local dist = ball.toPointDist(tmpP)
		if IS_SIMULATION then
			return dist
		else
			dist = dist * 0.6 - 38
			-- dist = dist * 0.4857 - 16.19
			if dist <= 60 then
				dist = 60
			end
			return dist
		end
	end
end