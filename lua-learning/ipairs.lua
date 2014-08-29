

local function iter(a,i)
	i = i + 1
	local v = a[i]
	if v then 
		return i, v
	end
end

function ipairs(a)
	return iter, a, 0
end

--test
a = {[1] = 54, [2] = 3445, [3] = 100, [6] = 55,}
for i, v in ipairs(a) do
	print(i, v)
end


