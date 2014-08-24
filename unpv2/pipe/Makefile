all: mainpipe fduplex

mainpipe: mainpipe.o error.o wrapstdio.o wrapunix.o client.o server.o 
	gcc -o mainpipe mainpipe.o error.o wrapstdio.o wrapunix.o client.o server.o

fduplex: fduplex.o error.o wrapstdio.o wrapunix.o client.o server.o 
	gcc -o fduplex fduplex.o error.o wrapstdio.o wrapunix.o client.o server.o

error.o: error.c unpipc.h
	gcc -c  error.c

wrapstdio.o: wrapstdio.c unpipc.h
	gcc -c wrapstdio.c

wrapunix.o : wrapunix.c unpipc.h
	gcc -c wrapunix.c

client.o : client.c unpipc.h
	gcc -c client.c

server.o : server.c unpipc.h
	gcc -c server.c
