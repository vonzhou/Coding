
all : mqunlink

mqunlink : mqunlink.o  wrapunix.o  error.o unpipc.h
	gcc -o mqunlink mqunlink.o  wrapunix.o  error.o -lrt 
