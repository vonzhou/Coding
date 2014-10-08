
-- convert list of decimal numbers to hex
require("string")

local a =1
while arg[a] do
    --print(arg[a])
    print(string.format("%d = 0x%x \n", arg[a], arg[a]))
    a =a + 1
end



