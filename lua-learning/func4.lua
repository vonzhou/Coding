
function foo(x) 
	print("in foo 1 ..\n")
	return x * 3 
end

foo = function(x) 
	print("in foo 2 .. \n")
	return x * 3 
end

print(foo(3))
print("\n")




