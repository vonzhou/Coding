#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 50

int main(void){
	int fd[2];
	int error;
	char *str="hello , world!";
	char buf[BUF_SIZE];
	
	if(socketpair(AF_UNIX,SOCK_STREAM,0,fd) == -1){
		printf("ERR:create socket pair failed:%s\n",strerror(errno));
		exit(-1);
	}
	//在一个进程中，在流管道的一端写入，可以从另一端读取；
	if((error = write(fd[0],str,strlen(str))) == -1){
		printf("ERR:write error:%s\n",strerror(errno));
		exit(-1);
	}
/*	//在同一端写读会发生阻塞	
	if((error = read(fd[0],buf,sizeof(buf))) == -1){
                printf("ERR:read error:%s\n",strerror(errno));
                exit(-1);
        }	
*/
	if((error = read(fd[1],buf,sizeof(buf))) == -1){
		printf("ERR:read error:%s\n",strerror(errno));
                exit(-1);
        }
	printf("GET:%s\n",buf);
	return 0;
}	
