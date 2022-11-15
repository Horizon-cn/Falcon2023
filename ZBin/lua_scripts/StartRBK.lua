package.path = package.path .. ";./lua_scripts/?.lua"
package.path = package.path .. ";./lua_scripts/utils/?.lua"
package.path = package.path .. ";./lua_scripts/worldmodel/?.lua"
package.path = package.path .. ";./lua_scripts/robot/?.lua"
package.path = package.path .. ";./plugins/?.lua"

--print("starting RBK")
-- package.path = package.path .. ";./lua_scripts/plugins/?.lua"

require("utils")
require("task")