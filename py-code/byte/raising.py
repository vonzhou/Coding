#!/usr/bin/python
#filename:raising.py

class ShortInputException(Exception):
	def __init__(self, length, atleast):
		Exception.__init__(self,length, atleast)
		self.length = length
		self.atleast = atleast

try:
	s = raw_input('Enter some txt:')
	if len(s) < 3:
		raise ShortInputException(len(s),3)
except EOFError:
		print 'Make sure to input something'
except ShortInputException,x:
	print 'ShortINputException occurred,length is %d,\
		but at least should be %d' % (x.length, x.atleast)
except:
	print '==='
else:
	print 'No ,exception.'




