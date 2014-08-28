Person = {}

function Person:new(p)

	local obj = p
	if(obj == nil) then
		obj = {name="vonzhou", age=34, other=true}
	end

	self.__index = self  -- ???????

	return setmetatable(obj,self)

end

function Person:toString()

	return self.name..":"..self.age..":"..(self.other and "handsome" or "ugly")
end

me = Person:new()
print(me:toString())
