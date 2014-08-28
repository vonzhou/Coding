
-- how does it work ???

function myPower(x)
	return function(y) return y ^ x end
end

power2 = myPower(2)
power3 = myPower(3)

print(power2(4))
print(power3(4))
