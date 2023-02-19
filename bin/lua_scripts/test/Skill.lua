gSkillTable = {}

for _, value in ipairs(gSkill) do
	local filename = LUA_SCRIPTS_SKILL_PATH ..value..".lua"
	dofile(filename)
end

function gSkillTable.CreateSkill(spec)
	assert(type(spec.name) == "string")
	--print("Init Skill: "..spec.name)	
	gSkillTable[spec.name] = spec
	return spec
end
