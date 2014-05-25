default:tcpserver tcpclient

tcpserver:tcpserver01.o wrapsock.o str_echo.o writen.o util.h error.o wrapunix.o
	cc -o tcpserver tcpserver01.o wrapsock.o str_echo.o writen.o error.o wrapunix.o
tcpserver01.o:tcpserver01.c util.h
	cc -c tcpserver01.c
wrapsock.o:wrapsock.c util.h
	cc -c wrapsock.c


tcpclient:tcpcli01.o wrapsock.o writen.o str_cli.o util.h error.o wrapunix.o wrapstdio.o readline.o
	cc -o tcpclient tcpcli01.o wrapsock.o  writen.o str_cli.o error.o wrapunix.o wrapstdio.o readline.o

clean:
	rm -f *.o tcpserver tcpclient








