
all : send recv  

send : mqsend.o  wrapunix.o  error.o unpipc.h
	gcc -o send mqsend.o  wrapunix.o  error.o -lrt 
recv : mqrecv.o  wrapunix.o  error.o unpipc.h
	gcc -o recv mqrecv.o  wrapunix.o  error.o -lrt 
