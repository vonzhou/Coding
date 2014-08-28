
a = {1,34,45,0,-34,-1,0,}
local found = nil
for i=1, #a do
	if a[i] < 0 then
		found = i;
		break
	end
end
print(found)
