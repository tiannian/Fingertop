local co1 = coroutine.create(function(x)
  for i=1,10 do coroutine.yield(x+i) end
  return x+99
end)

print(coroutine.resume(co1,1))
local co2 = coroutine.fork(co1)
print(coroutine.resume(co2,1))
print(coroutine.status(co1))
print(coroutine.status(co2))


for i=1,4 do
  print("co1", coroutine.resume(co1))
  print("co2", coroutine.resume(co2))
end


