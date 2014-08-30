
Set = {}

--create a new set from the list
function Set.new(list)
	local set = {}
	for _, v in ipairs(list) do
		set[v] = true
	end

	return set
end

function Set.union(a,b)
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
Set.print(sa)
Set.print(sb)

local res = Set.union(sa, sb)
local res2 = Set.intersection(sa, sb)
Set.print(res)
Set.print(res2)


