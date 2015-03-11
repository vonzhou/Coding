
all : mqattr

mqattr : mqgetattr.o  wrapunix.o  error.o unpipc.h
	gcc -o mqattr mqgetattr.o  wrapunix.o  error.o -lrt 
