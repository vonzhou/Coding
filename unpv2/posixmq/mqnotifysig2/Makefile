
all : mqnotifysig

mqnotifysig : mqnotifysig2.o  wrapunix.o  signal.o error.o unpipc.h
	gcc -o mqnotifysig mqnotifysig2.o  wrapunix.o  signal.o error.o -lrt 
