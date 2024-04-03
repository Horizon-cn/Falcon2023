gPlayTable.CreatePlay{

	firstState = "start",

	["start"] = {
    switch = function ()
      if true then
        return "start"
      end
    end,
<<<<<<< HEAD
    Kicker  = task.techdefence(),
=======
    Special  = task.techdefence(1),
    Assister=task.techdefence(2),
    Leader=task.techdefence(3),
>>>>>>> 6fc00ba2d41d4c28fe68f1337005ac8fe1a66584
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
