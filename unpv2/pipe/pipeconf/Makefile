
all : conf

conf : pipeconf.o wrapunix.o wrapstdio.o error.o unpipc.h
	gcc -o conf pipeconf.o  wrapunix.o wrapstdio.o error.o 
