
co = coroutine.create(function()
	for i=1, 10 do
		print("co",i)
		coroutine.yield()
	end
end)

for i=1,8 do
	coroutine.resume(co)
end

print(coroutine.status(co))

print(coroutine.resume(co))    -- to see the resume return value
