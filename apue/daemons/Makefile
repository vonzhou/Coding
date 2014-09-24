all: reread test_init
reread : reread.o single.o error.o  lockfile.o init.o
	gcc -o reread reread.o single.o error.o  lockfile.o init.o -lpthread
test_init: test_init.o init.o error.o
	gcc -o test_init test_init.o init.o error.o

test_init.o: test_init.c util.h
	gcc -c test_init.c
init.o: init.c util.h
	gcc -c init.c 
error.o : error.c util.h
	gcc -c error.c
single.o : single.c
	gcc -c single.c
lockfile.o : lockfile.c
	gcc -c lockfile.c
reread.o:reread.c util.h 
	gcc -c reread.c



clean :
	-rm reread test_init *.o
