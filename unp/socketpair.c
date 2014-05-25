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
	int pid;
	char *str="hello , world!";
	char buf[BUF_SIZE];
	
	if(socketpair(AF_UNIX,SOCK_STREAM,0,fd) == -1){
		printf("ERR:create socket pair failed:%s\n",strerror(errno));
		exit(-1);
	}

	if((pid = fork()) == 0){
		//child process
		close(fd[1]);
		if((error = write(fd[0],str,strlen(str))) == -1){
               		printf("ERR:write error:%s\n",strerror(errno));
                	exit(-1);
        	}
	}else if(pid > 0){
		// parent process read
		close(fd[0]);
		if((error = read(fd[1],buf,sizeof(buf))) == -1){
			printf("ERR:read error:%s\n",strerror(errno));
                	exit(-1);
        	}
		printf("Get from child:%s\n",buf);
	}else{
		printf("fork error!\n");
		exit(-1);
	}

	return 0;
}	
