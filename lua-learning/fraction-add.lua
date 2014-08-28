
fraction_a = {numerator=2, denominator=3}
fraction_b = {numerator=5, denominator=7}

fraction_op = {}

function fraction_op.__add(f1,f2)
	ret = {}
	ret.numerator = f1.numerator*f2.denominator + f2.numerator*f1.denominator
	ret.denominator = f1.denominator * f2.denominator
	return ret
end

setmetatable(fraction_a,fraction_op)
setmetatable(fraction_b,fraction_op)

fraction_s = fraction_a + fraction_b
print(fraction_s.numerator)
	
