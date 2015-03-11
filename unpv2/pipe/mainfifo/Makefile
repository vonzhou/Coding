
all : mainfifo

mainfifo : mainfifo.o client.o server.o wrapunix.o wrapstdio.o error.o unpipc.h
	gcc -o mainfifo mainfifo.o client.o server.o wrapunix.o wrapstdio.o error.o 
