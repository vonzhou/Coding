#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<sys/sysinfo.h>
#include<sys/select.h>
#include<sys/time.h>
#include<unistd.h>

#define MAX_SIZE 1024*1
#define SERV_PORT 2500


int sendUDP(char name[20],int sockfd,struct sockaddr *pservaddr,socklen_t servlen)
{
                char buf[MAX_SIZE];
                fd_set wrset;
                struct timeval tv;
                int rlen,wlen;
                int fd;
                int ret;
                int i;

                if(connect(sockfd,(struct sockaddr *)pservaddr,servlen) == -1)
                {
                        perror("connet error");
                        exit(-1);
                }
                else
                        printf("connect server ok!\n");

                fd = open(name,O_RDONLY);
                if(fd==-1)
                {
                        printf("fopen error %s\n",strerror(errno));
                        exit(-1);
                }
                
                i=0;
                
                while(1)
                {        
                        tv.tv_sec = 1;// tell select to wait 1 second;
                        tv.tv_usec = 0;
                        
                        FD_ZERO(&wrset);
                        FD_SET(sockfd,&wrset);
                        
                        ret = select(sockfd+1,NULL,&wrset,NULL,&tv);
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
                        
                        memset(buf,0,MAX_SIZE);
                        if(FD_ISSET(sockfd,&wrset))
                        {                                        
                                rlen = read(fd,buf,MAX_SIZE);
                                if(rlen <0)
                                {
                                        printf("fread data error %s\n",strerror(errno));
                                        exit(-1);
                                }
                                else if(rlen==0)
                                {
                                        wlen = write(sockfd,"end",3);
                                        if(wlen !=3)
                                        {
                                                printf("write end flag error:%s\n",strerror(errno));
                                                exit(-1);
                                        }

                                        printf("File %s Transfer Success!\n", name);

                                        close(fd);
                                        return 0;
                                }

                                wlen = write(sockfd,buf,rlen);
                                if(wlen != rlen)
                                {
                                        printf("write data to sockfd error:%s\n",strerror(errno));
                                        exit(-1);
                                }
                                
                                i++;
                                
                                usleep(500);
                                printf("The %d times read\n",i);
                        }
                }
        }


int main(int argc ,char *argv[])
{        
        char *fh;
        struct sysinfo s_info;
        long time1,time2;
        int error1,error2;
        int sockfd;
        struct stat fsize;
        struct sockaddr_in servaddr;
        error1= sysinfo(&s_info);
        time1 = s_info.uptime;
        int r;

        if(argc != 3)
        {
                printf("useage:udpclient<IPaddress>;\n");
                exit(1);
        }
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family= AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        
        if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
        {
                printf("[%s]is not a valid IPaddress\n",argv[1]);
                exit(1);
        }
        fh = argv[2];

        sockfd =socket(AF_INET,SOCK_DGRAM,0);
        
        r = fcntl(sockfd, F_GETFL, 0);
        fcntl(sockfd, F_SETFL, r & ~O_NONBLOCK);
        
        sendUDP(argv[2],sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));        
        close(sockfd);
	
	fprintf(stderr,"ServerIP:\t%s\n",argv[1]);        
        if(stat(argv[2],&fsize) == -1)
                perror("failed to get fiel statusi\n");
        else        
                fprintf(stderr,"file name:\t%s\nfile size:\t%dK\n",argv[2],fsize.st_size/1024);
        error2=sysinfo(&s_info);
        time2 = s_info.uptime;
        printf("tranfice file time =%ld seconds\n",(time2-time1));
}                
