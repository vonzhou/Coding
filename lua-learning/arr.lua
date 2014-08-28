

arr = {1,34,45,4589,}
for i = 1, #arr do
	print(arr[i])
end

arr2 = {"string", 100, function() print("in function") end }
arr2[3]()

-- arr is global variable
arr3 = _G.arr

print(arr3[1])

print("------------")
w = {x=0, y=0, label="console"}
x={math.sin(0), math.sin(1),math.sin(2)}
w[1] = "another"
x.f = w
print(w["x"])
print(w[1])
print(x.f[1])
w.x = nil














