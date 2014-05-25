#!/usr/bin/local
#Filename : using_dict.py

ab = {'vonzhou':'vonzhou@163.com',
	'chownvon':'hello@gmail.com',
	'luyna':'luyna@gmail.com',
	'zhou':'zhou@hust.edu.cn'
	}

print "vonzhou's address is %s" % ab['vonzhou']
#adding a key/value pair

ab['zhouf'] = 'zhouf@hust.edu.cn'

#del a pair
del ab['chownvon']

print '\nThere are %d contacts in the address book' % len(ab)

for name,address in ab.items():
	print 'Contact %s at %s' % (name,address)

if 'zhouf' in ab:
	print "zhouf's address is %s" % ab['zhouf']

