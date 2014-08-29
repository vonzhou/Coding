

N,M = 3,4

mt = {}
for i=1,N do
	mt[i] = {}  -- a new line
	for j=1,M do
		mt[i][j] = 1;
	end
end

function show(mt)
	for i=1,N do
		for j=1, M do
			--
			print(mt[(i-1)*M + j])
		end
	end
end

show(mt)    -- why cannot work ??????????


