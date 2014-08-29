

i = 33
local i = 0
f = loadstring("i=i+1;print(i)")
g = function() i=i+1;print(i) end

f()
g()
