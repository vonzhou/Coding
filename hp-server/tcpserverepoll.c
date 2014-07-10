#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <libgen.h>

#define MAXEVENTS 1024
#define BUF_SIZE 10

//set this descriptor non blocking
static int setnonblocking(int sfd){
  	int flags, s;

  	flags = fcntl(sfd, F_GETFL, 0);
  	if (flags == -1) {
      	perror ("fcntl");
      	return -1;
    }

  	flags |= O_NONBLOCK;
  	s = fcntl(sfd, F_SETFL, flags);
  	if (s == -1) {
      	perror ("fcntl");
      	return -1;
    }

  	return 0;
}

//
static int create_and_bind (char *port){
  	struct addrinfo hints;
  	struct addrinfo *result, *rp;
  	int s, sfd;

  	memset (&hints, 0, sizeof (struct addrinfo));
  	hints.ai_family = AF_UNSPEC;     //IPv4 IPv6通用
  	hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
  	hints.ai_flags = AI_PASSIVE;     //监听套接字；

  	//根据暗示得到所有可用的addrinfo
  	s = getaddrinfo (NULL, port, &hints, &result);
  	if (s != 0){
      	fprintf (stderr, "getaddrinfo: %s\n", gai_strerror (s));
      	return -1;
    }
   	//use the first addr to create socket
  	for (rp = result; rp != NULL; rp = rp->ai_next) {
      	sfd = socket (rp->ai_family, rp->ai_socktype, rp->ai_protocol);
      	if (sfd == -1)
        	continue;

      	s = bind (sfd, rp->ai_addr, rp->ai_addrlen);
      	if (s == 0) {
        	//bind success
          	break;
        }

      	close (sfd);//if bind failed we close this socket
    }

  if (rp == NULL) {
      	fprintf (stderr, "Could not bind\n");
      	return -1;
  }

  freeaddrinfo (result);

  return sfd;
}

// add EPOLLIN event of fd to the epollfd
void addfd(int epollfd, int fd, int enable_et){
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN;
	if(enable_et)
		event.events |= EPOLLET;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
}

//the level-trigger logic
void lt(struct epoll_event *events, int number, int epollfd, int listenfd){
	char buf[BUF_SIZE];
	int i;
	for(i = 0; i < number; i++){
		int sockfd = events[i].data.fd;
		//new client connection
		if(sockfd == listenfd){
			struct sockaddr_in client_addr;
			socklen_t client_addrlen = sizeof(client_addr);
			int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_addrlen);
			if(connfd < 0){
				perror("accept failed..");
				exit(-1);
			}
			//register this event
			addfd(epollfd, connfd, 0);
		}else if(events[i].events & EPOLLIN){
			//if there exists data unreaded , this code will invoke
			printf("sockefd %d read event trigger once\n", sockfd);
			int ret = recv(sockfd, buf, BUF_SIZE, 0);
			if(ret <= 0){
				printf("some read error or client closed.\n");
				close(sockfd); // will unregister
				continue;
			}
			printf("get %d bytes from client: %s\n", ret, buf);
		}else{
			// what we are not interested
			printf("something else happened\n");
		}
	}
}

//the edge-trigger logic
void et(struct epoll_event *events, int number, int epollfd, int listenfd){
    char buf[BUF_SIZE];
    int i;
    for(i = 0; i < number; i++){
        int sockfd = events[i].data.fd;
        //new client connection
        if(sockfd == listenfd){
            struct sockaddr_in client_addr;
            socklen_t client_addrlen = sizeof(client_addr);
            int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_addrlen);
            if(connfd < 0){
                perror("accept failed..");
                exit(-1);
            }
            //register this event and set edge trigger mode
            addfd(epollfd, connfd, 1);
        }else if(events[i].events & EPOLLIN){
            //in this mode , we should read all the data out once
            printf("sockefd %d read event trigger once\n", sockfd);
			while(1){
				memset(buf, 0, sizeof(buf));
				int ret = recv(sockfd, buf, BUF_SIZE, 0);
           		if(ret < 0){
					//for the nonblocking IO,the following errors indicate the read complete
					if(errno == EAGAIN || errno == EWOULDBLOCK){
						printf("read later\n");
						break;
					}
                	printf("some other error\n");
                	close(sockfd); // will unregister
                	break;
            	}else if(ret == 0){
					printf("client closed.\n");
					close(sockfd);
					break;
				}else{
					printf("get %d bytes from client: %s\n", ret, buf);
				}
			}
        }else{
            // what we are not interested
            printf("something else happened\n");
        }
    }
}


int main (int argc, char *argv[]){
  	int sfd, s;
 	int efd;
   	struct epoll_event event;
  	struct epoll_event events[MAXEVENTS];

  	if (argc < 2){
      	fprintf (stderr, "Usage: %s [port]\n", basename(argv[0]));
      	exit (EXIT_FAILURE);
    }

//	const char *ip = argv[1];
//	int port = atoi(argv[2]);

  	sfd = create_and_bind (argv[1]);
  	if (sfd == -1)
    	abort ();

  	//listen for connection coming
  	s = listen (sfd, SOMAXCONN);
  	if (s == -1) {
      	perror ("listen");
      	abort ();
    }
		
  	//create a epoll object
  	efd = epoll_create1 (0);
  	if (efd == -1) {
      	perror ("epoll_create");
      	abort ();
    }
	
	//add the listen socket to the event poll
	addfd(efd, sfd, 1); 
	
	while(1){
		int ret = epoll_wait(efd, events, MAXEVENTS, -1);
		if(ret < 0){
			printf("epoll wait failture..\n");
			break;
		}
		//et(events, ret, efd, sfd);
		lt(events, ret, efd, sfd);
	}
	

  	close (sfd);

	return EXIT_SUCCESS;
}


