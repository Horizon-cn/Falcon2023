module(..., package.seeall)

function FileRead(filename)
	local file = io.open(filename, "r")
	local result = file:read("*a")
	file:close()
	return result;
end

function loadJson()
	json = require("json")
end

function decodeJson(file)
	local result = json.decode(file)
	return result;
end
