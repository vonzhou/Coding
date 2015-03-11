
all : mqnotifysig

mqnotifysig : mqnotifysig3.o  wrapunix.o  signal.o error.o unpipc.h
	gcc -o mqnotifysig mqnotifysig3.o  wrapunix.o  signal.o error.o -lrt 
