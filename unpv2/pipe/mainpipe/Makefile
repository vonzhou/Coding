
all : mainpipe

mainpipe : mainpipe.o client.o server.o wrapunix.o wrapstdio.o error.o unpipc.h
	gcc -o mainpipe mainpipe.o client.o server.o wrapunix.o wrapstdio.o error.o 
