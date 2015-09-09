
all : fduplex

fduplex : fduplex.o  wrapunix.o wrapstdio.o error.o unpipc.h
	gcc -o fduplex fduplex.o wrapunix.o wrapstdio.o error.o 
