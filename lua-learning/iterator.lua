

--factory
function values(t)
	local i=0
	return function() 
		i = i +1 
		return t[i]
	end
end

t = {234,65,67,3,5667,78,67,68,}

--create a iterator
iter = values(t)

while true do
	local e = iter()
	if e== nil then break end
	print(e)
end

-------------------------------
--use for iteration , more easy
for e in values(t) do
	print(e)
end






	
