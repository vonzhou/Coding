#/usr/bin/python

import cPickle as p
#aslo can use pickle but cPickle is faster 1000x

shoplist = ['apple', 'mango', 'pear']
shoplistfile = 'shoplist.dat'

#write this object to the file
f = file(shoplistfile,'w')
p.dump(shoplist, f)
f.close()

del shoplist

#readback from the file
f = file(shoplistfile)
storedlist = p.load(f)
print storedlist
