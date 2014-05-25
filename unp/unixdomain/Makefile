all: mycat openfile
mycat : error.o  wrapunix.o  my_open.o wrapsock.o read_fd.o  
	gcc -o mycat mycat.c error.o  my_open.o wrapunix.o wrapsock.o read_fd.o  
openfile : error.o write_fd.o
	gcc -o openfile openfile.c error.o write_fd.o

error.o : error.c util.h
	gcc -c error.c
wrapunix.o : wrapunix.c util.h
	gcc -c wrapunix.c
my_open.o : my_open.c util.h
	gcc -c my_open.c
wrapsocket.o : wrapsock.c util.h
	gcc -c wrapsock.c
read_fd.o : read_fd.c util.h
	gcc -c read_fd.c
write_fd.o : write_fd.c util.h
	gcc -c write_fd.c

	

 
clean :
	-rm  *.o
