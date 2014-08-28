
stars = {[1] = "Sun",[2]="Moon",[4]="Earth"}
for i,v in pairs(stars) do
	print(i,v)
end

print("--------------")

for i,v in ipairs(stars) do
	print(i,v)
end
