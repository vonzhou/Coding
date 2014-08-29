

co = coroutine.create(function(a, b, c)
	print("co",a, b, c)
end)

coroutine.resume(co, 2, 4, 5)
