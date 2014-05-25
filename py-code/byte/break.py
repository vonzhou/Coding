#!/usr/bin/python

while True:
	s = raw_input('Enter a string: ')
	if ('quit'==s):
		print 'The loop is exited.'
		break;
	print 'The len of your input is: ',len(s)
print 'Done'
