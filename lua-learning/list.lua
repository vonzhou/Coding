
local function getnext(list, node)
	if not node then
		return list
	else
		return node.next
	end
end

function traverse(list)
	return getnext, list, nil
end


list = nil
for line in io.lines() do
	list = {val = line, next = list}  -- head insertion
end

for node in traverse(list) do
	print(node.val)
end


