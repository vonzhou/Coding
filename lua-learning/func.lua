
function newCounter()
	local i = 0
	return function()   -- anonymous function
		i = i + 1
		return i
	end
end

c1 = newCounter()   -- function pointer ??

print(c1())
print(c1())


