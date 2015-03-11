
all : mqnotifysig

mqnotifysig : mqnotifysig4.o  wrapunix.o  signal.o error.o unpipc.h
	gcc -o mqnotifysig mqnotifysig4.o  wrapunix.o  signal.o error.o -lrt 
