


--P56
function add(...)
	local s=0
	for i,v in ipairs{...} do
		s = s+v
	end

	return s
end

print(add(3,45,76,43,2,4))

