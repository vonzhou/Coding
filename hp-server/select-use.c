#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h> //basename
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <errno.h>


int main(int argc, char *argv[]){
	int i, maxi;
	char buf[1024];
    fd_set read_fds, all_read_fds;
    fd_set exception_fds, all_exception_fds;
    int nready, connectfd[FD_SETSIZE];	
	int connfd,sockfd,maxfd;
	
	struct sockaddr_in client_address;
    socklen_t client_addrlen = sizeof(client_address);
	
	if(argc <= 2){
		printf("usage: %s ip_address port_number\n", basename(argv[0]));
		return 1;
	}

	const char *ip = argv[1];
	int port = atoi(argv[2]);
	
	int ret = 0;
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &address.sin_addr);
	address.sin_port = htons(port);

	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(listenfd >= 0);
	ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
	assert(ret != -1);
	ret = listen(listenfd, 5);
	assert(ret != -1);

	maxfd = listenfd;
	maxi = -1;
	for(i= 0; i < FD_SETSIZE; i++)
		connectfd[i] = -1;	
	FD_ZERO(&all_read_fds);
	FD_ZERO(&all_exception_fds);
	FD_SET(listenfd, &all_read_fds);
	//do not care about the OOB of listen socket

	while(1){
		read_fds = all_read_fds;
		exception_fds = all_exception_fds;
		memset(buf, 0, sizeof(buf));
		nready = select(maxfd + 1, &read_fds, NULL, &exception_fds, NULL);
		//new client connection coming
		if(FD_ISSET(listenfd, &read_fds)){
			connfd = accept(listenfd, (struct sockaddr *)&client_address, &client_addrlen);
			if(connfd < 0){
				perror("accept failed\n");
				exit(-1);
			}
		
			for(i=0; i < FD_SETSIZE; i++)
				if(connectfd[i] < 0){
					connectfd[i] = connfd;
					break;
				}
			if( i == FD_SETSIZE){
				printf("too many clients..\n");
				exit(-1);
			}
			// add new descriptor to the read set and exception set
			FD_SET(connfd, &all_read_fds);
			FD_SET(connfd, &all_exception_fds);
			if(connfd > maxfd)
				maxfd = connfd;
			if(i > maxi)
				maxi = i;// update the max index in connectfd[]
			//we complete the listen socktet processing
			if(--nready <= 0)
				continue;
		}
		for(i = 0; i <= maxi; i++){
			//check all the connected clients for data
			if((sockfd = connectfd[i]) < 0)
				continue;
			if(FD_ISSET(sockfd, &read_fds)){
				ret = recv(sockfd, buf, sizeof(buf) - 1, 0);
				if(ret <= 0)
					break;//connection closed
				// process logic
				printf("get %d bytes of normal data:%s\n", ret, buf);
			}else if(FD_ISSET(sockfd, &exception_fds)){
				//handle exceptions
				//get out of band data 
				ret = recv(connfd, buf, sizeof(buf) - 1, MSG_OOB);
				if(ret <= 0)
					break;
				printf("get %d bytes of OOB data: %s", ret, buf);
			
			}
			FD_CLR(sockfd, &all_read_fds);
			FD_CLR(sockfd, &all_exception_fds);
			//after we deal with this client
			close(sockfd);
			if(--nready <= 0)
				break;
		}
	}

	close(listenfd);
	return 0;
}
















