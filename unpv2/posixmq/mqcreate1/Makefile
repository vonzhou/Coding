
all : mqcreate

mqcreate : mqcreate1.o  wrapunix.o  error.o unpipc.h
	gcc -o mqcreate mqcreate1.o  wrapunix.o  error.o -lrt 
