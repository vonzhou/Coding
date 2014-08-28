

vonzhou = {name = "hh", age = 37, email = "sdfkj@ljdfsl"}

-- the CRUD ops
vonzhou.isHandsome = True
local age = vonzhou.age
vonzhou.email = "vonzhou@163.com"
vonzhou.name = nil

print(vonzhou.name)
print(vonzhou.email)


print("------------------")

for k, v in pairs(vonzhou) do
	print(k,v)
end


