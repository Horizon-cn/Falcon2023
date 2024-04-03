gPlayTable.CreatePlay{

	firstState = "start",

	["start"] = {
    switch = function ()
      if true then
        return "start"
      end
    end,
<<<<<<< HEAD
    Kicker   = task.tech3pass(),
    Tier = task.tech3pass(),
    Receiver = task.tech3pass(),
=======
    Leader   = task.tech3pass(),
    Assister=task.tech3pass(),
    Special=task.tech3pass(),
>>>>>>> 6fc00ba2d41d4c28fe68f1337005ac8fe1a66584
    -- Assister = task.markingFront("First"),
    -- Special  = task.markingFront("Second"),
    match    = "[L][S][A]"
  },
  name = "Test_Tech3Pass",
  applicable = {
  	exp = "a",    
  	a = true
  },
  attribute = "attack",
  timeout = 99999

}