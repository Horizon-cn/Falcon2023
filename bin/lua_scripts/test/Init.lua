print("Init Now")
-- lua_scripts相对于Core.exe的路径，重要
LUA_SCRIPTS_PATH = "../lua_scripts/test/"
LUA_SCRIPTS_OPPONENT_PATH = "../lua_scripts/test/opponent/"
LUA_SCRIPTS_REFPLAY_PATH = "../lua_scripts/test/play/Ref/"
LUA_SCRIPTS_TESTPLAY_PATH = "../lua_scripts/test/play/Test/"
LUA_SCRIPTS_SKILL_PATH = "../lua_scripts/test/skill/"
LUA_SCRIPTS_UTILS_PATH = "../lua_scripts/test/utils/"
LUA_SCRIPTS_WORLDMODEL_PATH = "../lua_scripts/test/worldmodel/"

-- 引用该目录下的.lua文件
package.path = package.path .. ";" .. LUA_SCRIPTS_PATH .. "?.lua"
package.path = package.path .. ";" .. LUA_SCRIPTS_OPPONENT_PATH .. "?.lua"
package.path = package.path .. ";" .. LUA_SCRIPTS_REFPLAY_PATH .. "?.lua"
package.path = package.path .. ";" .. LUA_SCRIPTS_TESTPLAY_PATH .. "?.lua"
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
require("RoleMatch") -- todo
for role, id in pairs(config.gRoleFixNum) do
	gRoleFixNum[role] = id
end

-- 先加载必要的工具函数

-- Skill初始化
gSkill = {}
gSkill = config.gSkill
require("Skill") -- todo

-- Play初始化
if not param.IS_YELLOW then
	gReadyPlay = config.gReadyPlay.blue
else
	gReadyPlay =  config.gReadyPlay.yellow
end
--gRefPlay = {}
gTestPlay = {}
--gRefPlay = config.gRefPlay
gTestPlay = config.gTestPlay
require("Play")
-- todo
-- OPPONENT_NAME = config.OPPONENT_NAME
-- local opponent = file.decodeJson(file.FileRead(LUA_SCRIPTS_OPPONENT_PATH .. OPPONENT_NAME .. ".json"))
-- require(OPPONENT_NAME)
