

function receive(prod)
	local status, value = coroutine.resume(prod)
	return value
end

function send(x)
	coroutine.yield(x)
end

function producer()
	return coroutine.create(function()
		while true do
			local x = io.read()
			send(x)
		end
	end)
end

function filter(prod)
	return coroutine.create(function()
		for line=1, math.huge do
			local x = receive(prod)
			x = string.format("%5d %s",line,x)
			send(x)
		end
	end)
end

function consumer(prod)
	while true do
		local x = receive(prod)
		io.write(x, "\n")
	end
end

p=producer()
f=filter(p)
consumer(f)





	
