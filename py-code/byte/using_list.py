#!/usr/bin/python
#FIlename:using_list.py

#This ia my shopping list
shoplist = ['ipad2','kindle','iphone5s','mango']
print 'I hava', len(shoplist),'items to perchase'
print ' These items are:'
for item in shoplist:
	print item,

shoplist.append('rice')
print '\nNow the shopping list is ',shoplist

shoplist.sort()
print 'After sort the list is ',shoplist

print 'The first item is ',shoplist[0]
del shoplist[0]
print 'After del the first item list is:',shoplist
