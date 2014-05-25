#!/usr/bin/python
#filename: using_sys.py
import sys

print 'The command line args are:'
for i in sys.argv:
	print i

print '\n The PYTHONPATH is ',sys.path,'\n'

