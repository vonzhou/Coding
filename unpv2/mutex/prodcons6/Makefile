
all : prodcons

prodcons : prodcons6.o  wrapunix.o wrappthread.o error.o unpipc.h
	gcc -o prodcons prodcons6.o  wrapunix.o  wrappthread.o error.o unpipc.h -lrt 
