/*
 * Test UDP to receive sth from Floodlight controller !
 * 2014 - 12- 24
 */

#include "global.h"

#define SERV_PORT 5001
#define MAX 100
// we keep the received content in a file 
void recvFile(char name[20],int sockfd){
	
    int ret,fd;
	mode_t fdmode = (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    unsigned char mesg[MAX];
    int rlen, wlen, chunklen;
    int i;

    fd = open(name,O_RDWR|O_CREAT|O_APPEND,fdmode);
    if(fd == -1)        {
     	  printf("open file %s error:%s \n",name,strerror(errno));
    	  exit(-1);
    }
	while(1){
    	memset(mesg, 0, sizeof(mesg));
        printf("waiting on port : %d\n", SERV_PORT);
        rlen = recvfrom(sockfd, mesg, sizeof(mesg), 0, NULL, NULL);
		//printf("%d\n", rlen);
       	if(rlen < 0){
       		printf("read sockfd error %s\n",strerror(errno));
            exit(-1);
       	}
        // write what received to the file...
        wlen = write(fd, mesg, rlen);
	}
    close(fd);
}

int main(int argc, char *argv[])
{
        int sockfd;
        int r;
        struct sockaddr_in servaddr;

        sockfd = socket(AF_INET,SOCK_DGRAM,0); /*create a socket*/
	
        /*init servaddr*/
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(SERV_PORT);

        //bind address and port to socket*
        if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1)
        {
                perror("bind error");
                exit(-1);
        }

        //r = fcntl(sockfd, F_GETFL, 0);
        //fcntl(sockfd, F_SETFL, r & ~O_NONBLOCK);
        
        recvFile(argv[1],sockfd);
        return 0;

}
