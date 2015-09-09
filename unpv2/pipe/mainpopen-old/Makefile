
all : mainpopen

mainpopen : mainpopen.o  wrapunix.o wrapstdio.o error.o unpipc.h
	gcc -o mainpopen mainpopen.o wrapunix.o wrapstdio.o error.o 
