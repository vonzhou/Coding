sum = 2
repeat
	sum = sum ^ 2
	print(sum)
until sum > 1000

print("---------")

repeat
	line = io.read()
until line ~=""
print(line)

x = tonumber(line)
local sqr = x/2
repeat
	sqr = (sqr + x/sqr)/2
	local error = math.abs(sqr^2 -x )
until error < x/10000
