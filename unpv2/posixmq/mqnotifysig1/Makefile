
all : mqnotifysig

mqnotifysig : mqnotifysig1.o  wrapunix.o  signal.o error.o unpipc.h
	gcc -o mqnotifysig mqnotifysig1.o  wrapunix.o  signal.o error.o -lrt 
