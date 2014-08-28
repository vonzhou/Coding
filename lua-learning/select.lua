




function foo(...) 
	for i=1,select('#', ...) do
		local arg = select(i, ...)
		print(i,arg)
	end

end

foo(2,343,546546,6767)

