
all : mqnotify

mqnotify : mqnotifythread1.o  wrapunix.o  signal.o error.o unpipc.h
	gcc -o mqnotify mqnotifythread1.o  wrapunix.o  signal.o error.o -lrt 
