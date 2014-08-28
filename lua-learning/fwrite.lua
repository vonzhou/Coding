




--P57

-- use "..."

function fwrite(fmt, ...)
	return io.write(string.format(fmt, ...))
end

--fwrite()
fwrite("a\n")
fwrite("%d,%d\n",4,5)
fwrite("%s,%d\n","von", 56)

print("-----------")
