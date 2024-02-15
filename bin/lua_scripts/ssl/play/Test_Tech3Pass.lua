gPlayTable.CreatePlay{

	firstState = "start",

	["start"] = {
    switch = function ()
      if true then
        return "start"
      end
    end,
    Kicker   = task.tech3pass(),
    Tier = task.tech3pass(),
    Receiver = task.tech3pass(),
    -- Assister = task.markingFront("First"),
    -- Special  = task.markingFront("Second"),
    match    = ""
  },
  name = "Test_Tech3Pass",
  applicable = {
  	exp = "a",    
  	a = true
  },
  attribute = "attack",
  timeout = 99999

}