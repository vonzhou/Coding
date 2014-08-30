


function readOnly(t)
	local proxy = {}
	local mt = {
		__index = t,
		__newindex = function(t,k,v)
			error("attempt to update a read-only table", 2)
		end
	}

	setmetatable(proxy, mt)
	return proxy

end


days =readOnly{"Sunday", "Monday","Tuesday",}
print(days[2])
days[2] = "Noday"













