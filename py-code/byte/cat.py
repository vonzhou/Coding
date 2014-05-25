#!/usr/bin/python

import sys

def readfile(filename):
	'''Print file a the standard terminal.'''
	f = file(filename)
	while True:
		line = f.readline()
		if len(line)==0:
			break
		print line,
	f.close()

#scripts start from here
if len(sys.argv) < 2:
	print 'Do nothing'
	sys.exit()

if sys.argv[1].startswith('--'):
	option = sys.argv[1][2:]
	if option == 'version':
		print 'Version 0.1'
	elif option == 'help':
		print '''\
This program prints file to the standard terminal,
Any number of files can be specified,
Options include:--version,--help '''
	else:
		print 'Unkonwn option'
		sys.exit()
else:
	for filename in sys.argv[1:]:
		readfile(filename)
