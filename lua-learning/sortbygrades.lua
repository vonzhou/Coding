
names = {"vonzhou", "feng", "luan"}
grades = {vonzhou = 34, feng = 3, luan = 345}

--[[
network = {
	{name="vonzhou", IP="23.4545.324"},
	{name="vvv", IP = "3.46.56"},
	{name="luan", IP="345.56.56"},
	}
--]]

function sortbygrade(names, grades)
	-- the anonymous func can access extral func's local variable
	table.sort(names, function(a,b) return (grades[a] > grades[b]) end)
end

--call it
sortbygrade(names,grades)

for i,v in ipairs(names) do
	print(v)
end



