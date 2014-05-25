#!/usr/bin/python

def func():
	x = 2;
	print 'change x to ',x
	#global y = 34 ,is wrong
	global y
	y=100
	print 'change y to ',y

x=1
y=4
func()
print 'After func x=',x,' and y=',y
