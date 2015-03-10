#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include <sys/errno.h>

#define MAXLINE 100

int
main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in	servaddr;
	char	buff[MAXLINE];
	time_t	ticks;
    int res ;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(9999);	/* daytime server */

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	res = listen(listenfd,3);
    if(res <0){
        printf("listen error . errno is : %d\n", errno);
        exit(-1);
    }
	printf("listening...~\n");
	for ( ; ; ) {
	    connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        if(write(connfd, buff, strlen(buff)) != strlen(buff)){
            printf("server write error!");exit(-1);
        }

	    close(connfd);
	}
}

