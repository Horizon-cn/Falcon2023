print("Init Now")
-- lua_scripts相对于Core.exe的路径，重要
LUA_SCRIPTS_PATH = "../lua_scripts/test/"
LUA_SCRIPTS_OPPONENT_PATH = "../lua_scripts/test/opponent/"
LUA_SCRIPTS_PLAY_PATH = "../lua_scripts/test/play/"
LUA_SCRIPTS_SKILL_PATH = "../lua_scripts/test/skill/"
LUA_SCRIPTS_UTILS_PATH = "../lua_scripts/test/utils/"
LUA_SCRIPTS_WORLDMODEL_PATH = "../lua_scripts/test/worldmodel/"

-- 引用该目录下的.lua文件
package.path = package.path .. ";" .. LUA_SCRIPTS_PATH .. "?.lua"
package.path = package.path .. ";" .. LUA_SCRIPTS_OPPONENT_PATH .. "?.lua"
package.path = package.path .. ";" .. LUA_SCRIPTS_PLAY_PATH .. "?.lua"
package.path = package.path .. ";" .. LUA_SCRIPTS_SKILL_PATH .. "?.lua"
package.path = package.path .. ";" .. LUA_SCRIPTS_UTILS_PATH .. "?.lua"
package.path = package.path .. ";" .. LUA_SCRIPTS_WORLDMODEL_PATH .. "?.lua"

-- 比赛参数初始化
require("param")

-- 解析.json
require("file")

file.loadJson()
local config = file.decodeJson(file.FileRead(LUA_SCRIPTS_PATH .. "Config.json"))

-- 球员初始化
gRoleFixNum = {}
for role, id in pairs(config.gRoleFixNum) do
	gRoleFixNum[role] = id
end

require("RoleMatch") -- todo

-- 先加载必要的工具函数


-- Skill初始化
gSkill = {}
gSkill = config.gSkill
require("Skill")

-- RefPlay初始化
gRefPlay = {}
gTestPlay = {}
gRefPlay = config.gRefPlay
gTestPlay = config.gTestPlay
require("Play")

OPPONENT_NAME = config.OPPONENT_NAME
local opponent = file.decodeJson(file.FileRead(LUA_SCRIPTS_OPPONENT_PATH .. OPPONENT_NAME .. ".json"))
require(OPPONENT_NAME)

gReadyPlay = function ()
	if not param.IS_YELLOW then
		return config.gReadyPlay.blue
	else
		return config.gReadyPlay.yellow
	end
end
