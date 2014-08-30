
Window = {} 	-- a namespace

--create a prototype using default values
Window.prototype = {x=0, y=0, width=100, height=100}
Window.mt  = {} -- meta table

--constructor
function Window.new(o)    -- o is a table
	setmetatable(o,Window.mt)
	return o
end

Window.mt.__index =  Window.prototype

local w = Window.new{x=10, y=10}
print(w.width)

















