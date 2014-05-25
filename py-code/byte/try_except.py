#!/usr/bin/python
#filename:try_except.py

import sys

try:
	s = raw_input('Enter some thing:')
except EOFError:
	print '\n Should input some thing'
	sys.exit()
except:  #other exceptions
	print '\n Some other exceptions occurred'
	#we donot exit

print 'Done'
