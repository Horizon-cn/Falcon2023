gPlayTable.CreatePlay{

	firstState = "start",

	["start"] = {
    switch = function ()
      if true then
        return "start"
      end
    end,
    Leader   = task.advance(),
    Assister = task.markingFront("First"),
    Special  = task.markingFront("Second"),
    match    = "[L][AS]"
  },
  name = "Test_TechCh",
  applicable = {
  	exp = "a",
  	a = trued
  },
  attribute = "attack",
  timeout = 99999

}
