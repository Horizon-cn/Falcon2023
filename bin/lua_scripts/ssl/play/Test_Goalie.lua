gPlayTable.CreatePlay{

firstState = "goalie",

["goalie"] = {
	switch = function ()
		if true then
			return "goalie";
		end
	end,
	-- Defender = task.multiBack(3,1),
 --    Assister = task.multiBack(3,2),
 --    Hawk = task.multiBack(3,3),
    Assister = task.stop(),
  	 Special  = task.stop(),
    Leader   = task.stop(),
  -- Fronter  = task.stop(),
  -- Center   = task.stop(),
    Defender = task.stop(),
    Middle   = task.stop(),
	 Breaker  = task.stop(),
    Crosser  = task.stop(),
    Goalie   = task.stop(),
    match    = "[AMDLSBC]"
},

name = "Test_Goalie",
applicable ={
	exp = "a",
	a = true
},
attribute = "attack",
timeout = 99999
}