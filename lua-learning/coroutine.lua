
co = coroutine.create(function() print("hello") end)

print(co)

print(coroutine.status(co)) 

coroutine.resume(co)
print(coroutine.status(co))
