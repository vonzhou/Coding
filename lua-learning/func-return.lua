

-- P54

function foo0()
end

function foo1()
	return "a"
end

function foo2()
	return "a","b"
end


print(foo0())
print(foo1())
print(foo2())
print(foo2(),1)   -- only use one return value -a 
print(foo2().."vvv")

print("------------")

function foo(i) 
	if i==0 then return foo0()
	elseif i==1 then return foo1()
	elseif i==2 then return foo2()
	else return "invalid"
	end
end
print(foo(1))
print(foo(2))
print(foo(2).."zhou")
print(foo(100))


