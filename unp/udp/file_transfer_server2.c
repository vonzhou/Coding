#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<sys/select.h>
#include<sys/time.h>
#include<unistd.h>
#include<sys/types.h>

#define SERV_PORT 2500
#define MAX_SIZE 1024*40

void recvUDP(char name[20],int sockfd)
{
        int ret,fd;
        mode_t fdmode = (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        char mesg[MAX_SIZE];
        fd_set rdset;
        struct timeval tv;
        int rlen,wlen;
        int i;

        fd = open(name,O_RDWR|O_CREAT|O_APPEND,fdmode);
        if(fd == -1)
        {
                printf("open file %s error:%s \n",name,strerror(errno));
                exit(-1);
        }

        for(i=0;;i++)
        {
                tv.tv_sec = 1;
                tv.tv_usec = 0;

                FD_ZERO(&rdset);
                FD_SET(sockfd,&rdset);
                
                ret = select(sockfd+1,&rdset,NULL,NULL,&tv);
                if(ret == -1)
                {
                        printf("select error %s\n",strerror(errno));
                        exit(-1);
                }
                else if(ret==0)
                {
                        printf("select timeout,continue circle\n");
                        continue;
                }
                
                if(FD_ISSET(sockfd,&rdset))
                {
                        memset(mesg,0,MAX_SIZE);
                        rlen = read(sockfd,mesg,MAX_SIZE);
                        if(rlen <=0 )
                        {
                                printf("read error %s\n",strerror(errno));
                                exit(-1);
                        }
                        
                        if(!strcmp(mesg,"end"))
                        {
                                printf("recv end.\n");
                                break;
                        }

                        wlen = write(fd,mesg,rlen); // write to file
                        if(wlen != rlen )
                        {
                                printf("write error %s\n",strerror(errno));
                                exit(-1);
                        }        
                }
                
                printf("The %d times write\n",i);
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

        /*bind address and port to socket*/
        if(bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1)
        {
                perror("bind error");
                exit(-1);
        }

        r = fcntl(sockfd, F_GETFL, 0);
        fcntl(sockfd, F_SETFL, r & ~O_NONBLOCK);
        
        recvUDP(argv[1],sockfd);

        return 0;

}
