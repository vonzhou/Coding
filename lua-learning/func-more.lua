

network = {
	{name="vonzhou", IP="23.4545.324"},
	{name="vvv", IP = "3.46.56"},
	{name="luan", IP="345.56.56"},
	}

table.sort(network, function(a,b) return (a.name > b.name) end)

for i,v in ipairs(network) do
	print(v.name)
end



