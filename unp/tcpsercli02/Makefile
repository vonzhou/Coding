default:tcpserver tcpclient

tcpserver:tcpserver02.o wrapsock.o str_echo.o writen.o util.h error.o wrapunix.o signal.o
	cc -o tcpserver tcpserver02.o wrapsock.o str_echo.o writen.o error.o wrapunix.o signal.o
tcpserver01.o:tcpserver02.c util.h
	cc -c tcpserver02.c
wrapsock.o:wrapsock.c util.h
	cc -c wrapsock.c


tcpclient:tcpcli01.o wrapsock.o writen.o str_cli.o util.h error.o wrapunix.o wrapstdio.o readline.o
	cc -o tcpclient tcpcli01.o wrapsock.o  writen.o str_cli.o error.o wrapunix.o wrapstdio.o readline.o

clean:
	rm -f *.o tcpserver tcpclient








