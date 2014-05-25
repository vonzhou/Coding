def buildConnStr(params):
	"""Build a connection string form a dictionary of params.
	Return string."""
	return ";".join(["%s=%s" %(k,v) for k,v in params.items()])

if __name__=="__main__":
	myParams={"server":"de15",\
		"database":"master",\
		"uid":"sa",\
		"pwd":"secret"\
	}

	print buildConnStr(myParams)

