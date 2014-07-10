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

#define MAXEVENTS 64

//set this socket non blocking
static int make_socket_non_blocking (int sfd){
  	int flags, s;

  	flags = fcntl (sfd, F_GETFL, 0);
  	if (flags == -1) {
      	perror ("fcntl");
      	return -1;
    }

  	flags |= O_NONBLOCK;
  	s = fcntl (sfd, F_SETFL, flags);
  	if (s == -1) {
      	perror ("fcntl");
      	return -1;
    }

  	return 0;
}

//根据端口号，创建套接字
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

int main (int argc, char *argv[]){
  	int sfd, s;
 	int efd;
   	struct epoll_event event;
  	struct epoll_event *events;

  	if (argc != 2){
      	fprintf (stderr, "Usage: %s [port]\n", argv[0]);
      	exit (EXIT_FAILURE);
    }

  	sfd = create_and_bind (argv[1]);
  	if (sfd == -1)
    	abort ();

  	s = make_socket_non_blocking (sfd);
  	if (s == -1)
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

  	event.data.fd = sfd;
  	//register the event we interested
  	event.events = EPOLLIN | EPOLLET;//边沿触发（Level Triggered，电平触发）
  	s = epoll_ctl (efd, EPOLL_CTL_ADD, sfd, &event);
  	if (s == -1){
      	perror ("epoll_ctl");
      	abort ();
    }

  	/* Buffer where events are returned */
  	events = calloc (MAXEVENTS, sizeof event);

  	/* The event loop */
	while (1) {
    	int n, i;

      	n = epoll_wait (efd, events, MAXEVENTS, -1);
      	//some events happened
      	for (i = 0; i < n; i++) {
        	if ((events[i].events & EPOLLERR) ||
              	(events[i].events & EPOLLHUP) ||
              	(!(events[i].events & EPOLLIN))){
            	/* An error has occured on this fd, or the socket is not
                 ready for reading (why were we notified then?) */
              	fprintf (stderr, "epoll error\n");
              	close (events[i].data.fd);
              	continue;
            }

          	else if (sfd == events[i].data.fd){
               //the listening socket become ready indicate the new connection coming
				while (1){
                	struct sockaddr in_addr;
                  	socklen_t in_len;
                  	int infd;
                  	char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

                  	in_len = sizeof in_addr;
                  	infd = accept (sfd, &in_addr, &in_len);
                  	if (infd == -1) {//some error occured
                    	if ((errno == EAGAIN) ||(errno == EWOULDBLOCK)){
                    		/* We have processed all incoming connections. */
                        	break;
                    	}
                    	else {
                    		perror ("accept");
                        	break;
                    	}
               		}
					//get the host and service expression from this socket addr
                   	s = getnameinfo (&in_addr, in_len, hbuf, sizeof hbuf, sbuf, sizeof sbuf,NI_NUMERICHOST | NI_NUMERICSERV);
		  			//
                  	if (s == 0) {
                    	printf("Accepted connection on descriptor %d (host=%s, port=%s)\n", infd, hbuf, sbuf);
                    }

		  			// make this connected socket nonblocking,add it to the event loop
                  	s = make_socket_non_blocking (infd);
                  	if (s == -1)
		            	abort ();

                  	event.data.fd = infd;
                  	event.events = EPOLLIN | EPOLLET;// readable , and edge trigger
                  	s = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
                  	if(s == -1){
                    	perror ("epoll_ctl");
                      	abort ();
                    }
                }
              	continue;
            }
          	else {
				// events about the connected socket happened,we should read all the data out
				// bcse in the edge mode
              	int done = 0;

              	while (1){
                  	ssize_t count;
                  	char buf[512];
			
                  	count = read (events[i].data.fd, buf, sizeof buf);
                  	if (count == -1) {
                     
						//在非阻塞模式下errno == EAGAIN不代表错误，说明已读到全部数据；
                      	if (errno != EAGAIN){
                          	perror ("read");//some other error
                          	done = 1;
                        }
                      	break;
                    }
                  	else if(count == 0){
                      //EOF, client close this connection (recv FIN)
                      done = 1;
                      break;
                    }

                  	/* Write the buffer to standard output */
                  	s = write (1, buf, count);
                  	if(s == -1){
                      	perror ("write");
                      	abort ();
                    }
                }

              	if (done){//每次处理完一个客户端的请求就关闭对应的connfd；
                  	printf ("Closed connection on descriptor %d\n", events[i].data.fd);

                  	/* Closing the descriptor will make epoll remove it
                     from the set of descriptors which are monitored. */
                 	close (events[i].data.fd);
                }
            }
        }
    }

  free (events);

  close (sfd);

  return EXIT_SUCCESS;
}


