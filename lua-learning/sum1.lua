sum = 0
num = 1

while num<=100 do
	sum = sum + num
	num = num + 1
end

print("sum=",sum)

print("----------------")

function add(a)
	local sum=0
	for i,v in ipairs(a) do
		sum = sum + v
	end

	return sum
end

a = { 23,45,-444,3,464545,}

print(add(a))

print("----------------")

s = "hello lasdjflsdajflsadjf vonzhou lsfjlsadjflsdf vonzhou"
a,b = string.find(s, "vonzhou")

print(a,b)
