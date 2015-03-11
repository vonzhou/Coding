
all : prodcons

prodcons : prodcons3.o  wrapunix.o wrappthread.o error.o unpipc.h
	gcc -o prodcons prodcons3.o  wrapunix.o  wrappthread.o error.o unpipc.h -lrt 
