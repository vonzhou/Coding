#!/usr/bin/env python
# Filename: while.py

number=23
running=True

while running:
	guess=int(raw_input('Enter an integer : '))

	if guess==number:
		print 'Congratulations, you guessed it.'
		running=False # this causes the while loop to stop
	elif guess<number:
		print 'No, what you guess is small.'
	else:
		print 'No, what you guess is big.'
else:
	print 'The while loop is over.'
	# Do anything else you want to do here

print 'Done'


