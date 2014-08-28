

function max(a)
	local mi=1
	local m=a[mi]
	for i,val in ipairs(a) do
		if val > m then
			mi=i
			m=val
		end
	end

	return m,mi
end

a = {34,45,4,76,09,-23,43,2323,3,}

print(max(a))
