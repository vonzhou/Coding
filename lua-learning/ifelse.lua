age = 5
sex = "male"
if age==40 and sex=="male" then
	print("man of 40 is flower");
elseif age > 60 and sex~="femal" then
	print("old man....\n");
elseif age < 20 then
	io.write("too youn")
else
	local age = io.read()
	print("your age is "..age)
end
