

--table with default value
local key = {} 		-- the unique key
local mt = {__index = function(t) return t[key] end}
function setDefault(t, d)
	t[key] = d
	setmetatable(t, mt)
end

tab = { x=10, y =20,}
print(tab.x, tab.z)
setDefault(tab, 0)
print(tab.x, tab.z)
























