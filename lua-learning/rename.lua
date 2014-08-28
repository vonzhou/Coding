

function rename(arg)
	return os.rename(arg.old,arg.new)
end

local arg = {["old"] = "hello.txt",["new"] = "new.txt"}

rename(arg)


