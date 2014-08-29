

function newCounter()
	local i=0
	return function()
		i = i+1
		return i
	end
end

c= newCounter()
for i=1,10 do
	print(c())
end

c1 = newCounter()
print(c1())
print(c())
