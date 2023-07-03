module(..., package.seeall)

-- 对task.lua更高一层的抽象,包括一些通过标志位决定的task和一些组合的task

function multiBack(n)
  taskTable={}
  for i=1,n do
    table.insert(taskTable,task.multiBack(n,i))
  end
  return taskTable
end