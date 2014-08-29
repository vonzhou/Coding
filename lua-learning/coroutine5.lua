

co = coroutine.create(function()
	print("co",coroutine.yield())
end)

print(coroutine.resume(co))
print(coroutine.resume(co, 20,10))


