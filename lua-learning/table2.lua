
a = {}
for i=1,10 do
	a[i]= io.read()
end

--print
for i=1, #a do
	print(a[i])
end

print(a[#a])
a[#a] = nil
