gPlayTable.CreatePlay{

	firstState = "start",

	["start"] = {
    switch = function ()
      if true then
        return "start"
      end
    end,
    Special  = task.techdefence(),
    Assister=task.techdefence(),
    Leader=task.techdefence(),
    -- Assister = task.markingFront("First"),
    -- Special  = task.markingFront("Second"),
    match    = "[L][S][A]"
  },
  name = "Test_TechDefence",
  applicable = {
  	exp = "a",    
  	a = true
  },
  attribute = "attack",
  timeout = 99999

}
