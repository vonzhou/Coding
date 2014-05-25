#!/usr/bin/python

poem = '''\
Programming with python fun.
work is fun.
'''

f = file('poem.txt','w')
f.write(poem)
f.close()

f = file('poem.txt') # the default open mode is read
while True:
	line = f.read();
	if len(line) == 0:
		break;
	print line,   #NB ,the ',' is to kill the last change line
f.close();

