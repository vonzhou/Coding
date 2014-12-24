/*--vonzhou
    A small UDP client ...
*/

#include "global.h"

#define SERV_PORT 5001

int main(int argc ,char *argv[])
{        
        char *fh;
        struct sysinfo s_info;
        long time1,time2;
        int error1,error2;
        int sockfd;
		int res;
        struct stat fsize;
        struct sockaddr_in servaddr;
        error1= sysinfo(&s_info);
        time1 = s_info.uptime;
        int r;
        char *buffer;
        if(argc != 2){  
            printf("useage:udpclient <IPaddress>;\n");
            exit(-1);
        }
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family= AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        
        if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0){
            printf("[%s]is not a valid IPaddress\n",argv[1]);
            exit(-1);
        }

        sockfd =socket(AF_INET,SOCK_DGRAM,0);
        buffer = "Hello";
        r = sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, 
                sizeof(struct sockaddr_in));   
        if(r < 0)
            perror("sendto failed ...");
        //r = fcntl(sockfd, F_GETFL, 0);
        //fcntl(sockfd, F_SETFL, r & ~O_NONBLOCK);
        
		
        close(sockfd);
	
}                
