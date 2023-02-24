gSkillTable = {}

for _, value in pairs(gSkill) do
	local filename = LUA_SCRIPTS_SKILL_PATH ..value..".lua"
	local skill = dofile(filename)
	if skill ~= nil then
		gSkillTable[value] = skill
	end
end

function gSkillTable.CreateSkill(spec)
	return spec
end
