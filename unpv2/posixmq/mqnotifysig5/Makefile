
all : mqnotifysig

mqnotifysig : mqnotifysig5.o  wrapunix.o  signal.o error.o unpipc.h
	gcc -o mqnotifysig mqnotifysig5.o  wrapunix.o  signal.o error.o -lrt 
