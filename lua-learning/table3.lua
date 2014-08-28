
i = 10
j = "10"
k = "+10"

a = {}
a[i] = "one"
a[j] = "two"
a[k]= "three"

print(a[i], a[j], a[k])
print(a[tonumber(k)])
