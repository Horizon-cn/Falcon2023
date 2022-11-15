module(..., package.seeall)

nothing      					= 0x00000000
slowly      					= 0x00000001
quickly	    					= 0x00000002
pos_only	 					= 0x00000004
accurately						= 0x00000008

dodge_ball						= 0x00000010
avoid_shoot_line 				= 0x00000020
not_avoid_their_vehicle			= 0x00000040
not_avoid_our_vehicle			= 0x00000080
avoid_stop_ball_circle          = 0x00000100
dodge_referee_area				= 0x00000200
not_dodge_penalty    		    = 0x00000400
dodge_our_defense_box			= 0x00000800

dribbling						= 0x00001000
not_dribble     				= 0x00002000
force_kick						= 0x00004000
kick_when_possiable				= 0x00008000

free_kick						= 0x00010000
turn_around_front				= 0x00020000
allow_dss						= 0x00040000	
ignore_player_close_to_target	= 0x00080000

their_baLL_placement            = 0x01000000
our_ball_placement              = 0x02000000