#!/usr/bin/python

while True:
	s = raw_input('Enter a string: ')
	if ('quit'==s):
		print 'The loop is exited.'
		break;
	if len(s)<5:
		continue
	print 'The len of your input < 5 cannot got here '
print 'Done'
