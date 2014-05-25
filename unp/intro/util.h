#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/un.h>

char *sock_ntop(const struct sockaddr *,socklen_t);
char *Sock_ntop(const struct sockaddr *,socklen_t);
