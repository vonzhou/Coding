
function fib(n)
	if n < 2 then 
		return 1
	end
	
	return fib(n-2) + fib(n-1)
end

fib100 = fib(10)

print(fib100)
