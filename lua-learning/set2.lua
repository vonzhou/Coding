
Set = {}
local mt = {}  -- the meta table 

--create a new set from the list
function Set.new(list)
	local set = {}
	setmetatable(set, mt)
	for _, v in ipairs(list) do
		set[v] = true
	end

	return set
end

function Set.union(a,b)
	if getmetatable(a) ~=mt or getmetatable(b) ~= mt then
		error("attempt to add a set with a non set value", 2)
	end
	local res = Set.new{}
	for k in pairs(a) do res[k]=true end
	for k in pairs(b) do res[k] = true end

	return res
end

function Set.intersection(a, b)
	local res = Set.new{}
	for k in pairs(a) do
		res[k] = b[k]	-- if nil , no exists
	end

	return res
end

function Set.tostring(set)
	local l = {} -- store all the elements in the set
	for e in pairs(set) do 
		l[#l + 1] = e
	end 

	return "{" .. table.concat(l,",") .. "}"
end

function Set.print(s)
	print(Set.tostring(s))
end

---------------test

local a = { 23,454,1,6767,78545,343,2356, 4,3,3,2,}
local b = {1, 2, 3, 4 , 4, 5, 8, 9, 10}

local sa = Set.new(a)
local sb = Set.new(b)
print(getmetatable(sa))
print(getmetatable(sb))

mt.__add = Set.union
mt.__mul = Set.intersection
Set.print(sa)
Set.print(sb)

local res = sa + sb 	--Set.union(sa, sb)
local res2 = sa * sb	--Set.intersection(sa, sb)
Set.print(res)
Set.print(res2)

--res = sa + 5  -- test error

mt.__le = function(a, b)
	for k in pairs(a) do
		if not b[k] then return false end
	end

	return true
end

mt.__lt = function(a, b)
	return a <= b and not (b <= a)
end

mt.__eq = function(a, b)
	return a <= b and b <= a
end


sa = Set.new{1,2,3,4,}
sb = Set.new{12,1,2,3,4,}
print(sa <= sb)
print(sa < sb)
print(sa ~= sb)


mt.__tostring = Set.tostring
sa = Set.new{2,4,56,}
print(sa)




















