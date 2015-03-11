
all : semcreate semunlink semgetvalue semwait sempost

semcreate : semcreate.o  wrapunix.o  error.o unpipc.h
	gcc -o semcreate semcreate.o  wrapunix.o  error.o -lrt 
semunlink : semunlink.o  wrapunix.o  error.o unpipc.h
	gcc -o semunlink semunlink.o  wrapunix.o  error.o -lrt 
semgetvalue : semgetvalue.o  wrapunix.o  error.o unpipc.h
	gcc -o semgetvalue semgetvalue.o  wrapunix.o  error.o -lrt 
semwait : semwait.o  wrapunix.o  error.o unpipc.h
	gcc -o semwait semwait.o  wrapunix.o  error.o -lrt 
sempost : sempost.o  wrapunix.o  error.o unpipc.h
	gcc -o sempost sempost.o  wrapunix.o  error.o -lrt 
