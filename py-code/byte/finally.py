#!/usr/bin/python

import time

try:
	f = file('poem.txt','r')
	while True:
		line = f.readline()
		if len(line)==0:
			break;
		time.sleep(3)
		print line
finally:
	f.close()
	print 'Exception occurred,file closed normally.'

	
