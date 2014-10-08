
-- convert list of hex numbers(headed with 0x..)  to decamal
require("string")

local a =1
while arg[a] do
    -- turn 0x.. to decimal
    de = tonumber(arg[a])
    print(string.format("0x%x = %d \n", de, de))
    a =a + 1
end



