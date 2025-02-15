package.path = package.path .. ";../lua_scripts/ssl/skill/?.lua"
package.path = package.path .. ";../lua_scripts/ssl/play/?.lua"
package.path = package.path .. ";../lua_scripts/ssl/worldmodel/?.lua"
package.path = package.path .. ";../lua_scripts/ssl/utils/?.lua"
package.path = package.path .. ";../lua_scripts/ssl/opponent/?.lua"

print("Step in Zeus.lua")

ranStr = tostring(os.time()):reverse():sub(1,3)
math.randomseed(ranStr)

require(OPPONENT_NAME)
require("Skill")
require("Play")
require("cond")
require("pos")
require("dir")
require("flag")
require("param")
require("player")
require("ball")
require("enemy")
require("pre")
require("kp")
require("cp")
require("task")
require("kick")
require("bit")
require("bufcnt")
require("learn")
require("file")
require("score")
require("combo")

for _, value in ipairs(gSkill) do
	local filename = "../lua_scripts/ssl/skill/"..value..".lua"
	dofile(filename)
end

for _, value in ipairs(gPlay) do
	local filename = "../lua_scripts/ssl/play/"..value..".lua"
	dofile(filename)
end

