
all : prodcons

prodcons : prodcons2.o  wrapunix.o wrappthread.o error.o unpipc.h
	gcc -o prodcons prodcons2.o  wrapunix.o  wrappthread.o error.o unpipc.h -lrt 
