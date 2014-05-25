#/usr/bin/python

import httplib
conn = httplib.HTTPConnection('google.com')
conn.request('get','/')
print conn.getresponse().read()
conn.close()
