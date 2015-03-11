
all : server client 

server : server_main.o server.o wrapunix.o wrapstdio.o error.o unpipc.h
	gcc -o server server_main.o  server.o wrapunix.o wrapstdio.o error.o 
client : client_main.o client.o wrapunix.o wrapstdio.o error.o unpipc.h
	gcc -o client client_main.o  client.o wrapunix.o wrapstdio.o error.o 
