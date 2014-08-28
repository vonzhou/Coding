

days = {"Sunday", "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday", "Saturday",}

revDays = {}
for k, v in pairs(days) do
	revDays[v] = k
end

x = "Tuesday"
print(revDays[x])
