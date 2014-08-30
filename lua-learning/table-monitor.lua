
-- the origin table, maybe created in other parts
t = {12,45,33,10}

-- get a private access of t
local _t = t

-- a proxy
t = {}

local mt={
	__index = function(t,k)
		print("*access to element " .. tostring(k))
		return _t[k] 	-- access the original table
	end,
	__newindex = function(t,k,v)
		print("*update of element " .. tostring(k) .. " to " .. tostring(v))
		_t[k] = v  --update original table
	end
}
setmetatable(t, mt)

--t[2] = "hello"
print(t[2])
t[100] = "345"


