

local hello = require "hello_lib"

--------sin 1
print(hello.hello_sin(1))

---------map function

t = {1,2,3,4,5}
function zero()
	for i = 1, #t do 
		t[i] =0
	end
end

hello.hello_map(t, zero) 

for i=1, #t do
	print(t[1])
end












