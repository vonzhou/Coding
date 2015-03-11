
all : mainpipe

mainpipe : mainpipe.o client.o server.o wrapunix.o wrapstdio.o mesg_recv.o mesg_send.o error.o unpipc.h
	gcc -o mainpipe mainpipe.o client.o server.o wrapunix.o wrapstdio.o mesg_recv.o mesg_send.o error.o 
