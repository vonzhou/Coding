
all : prodcons

prodcons : prodcons1.o  wrapunix.o wrappthread.o error.o unpipc.h
	gcc -o prodcons prodcons1.o  wrapunix.o  wrappthread.o error.o unpipc.h -lrt 
