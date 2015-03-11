
all : mqcreate

mqcreate : mqcreate.o  wrapunix.o  error.o unpipc.h
	gcc -o mqcreate mqcreate.o  wrapunix.o  error.o -lrt 
