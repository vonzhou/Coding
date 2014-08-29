

function allwords()
	local line = io.read() -- current line
	local pos = 1          -- form index 1 in lua
	return function()
		while line do 
			local s,e = string.find(line, "%w+", pos)
			if s then
				pos = e + 1
				return string.sub(line, s, e)   -- return this word
			else
				line = io.read() 	-- next line
				pos = 1
			end
		end
		return nil	-- no line , io.read() return nil when EOF (ctrl+D)
	end
end

for word in allwords() do
	print(word)
end
