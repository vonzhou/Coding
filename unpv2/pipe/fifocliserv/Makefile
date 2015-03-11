
all : mainclient mainserver

mainserver : mainserver.o  wrapunix.o wrapstdio.o readline.o error.o unpipc.h
	gcc -o mainserver mainserver.o wrapunix.o wrapstdio.o readline.o error.o 
mainclient : mainclient.o  wrapunix.o wrapstdio.o readline.o error.o unpipc.h
	gcc -o mainclient mainclient.o wrapunix.o wrapstdio.o readline.o error.o 
