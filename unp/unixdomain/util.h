#ifndef UTIL_H
#define UTIL_H 1

#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/un.h>
#include<poll.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>



#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) 

//miscellaneous constants
#define BUFFSIZE 8192 // buffer size for reads and writes
#define MAXLINE 4096  // max text line length

//IO process;
void str_echo(int);
void  Writen(int fd,void *buf,size_t  n);
int Readn(int fd,void *buf,size_t n);
void str_cli(FILE * fp,int fd);
ssize_t Readline(int fd,void *,size_t); 
ssize_t Read(int fd,void *ptr, size_t nbytes);
void Write(int fd, void *ptr, size_t nbytes);


//wrapunix.c
pid_t Fork();
void Close(int fd);


//Error processing func prototype;
void err_sys(const char *fmt,...);
void err_quit(const char *fmt,...);

// socket process; implemented in wrapsock.c;
int Accept(int sockfd,struct sockaddr *sa,socklen_t *slenp);
void Bind(int sockfd,const struct sockaddr *sa,socklen_t len);
void Connect(int sockfd,const struct sockaddr *sa,socklen_t len);
void Getpeername(int fd,struct sockaddr *sa,socklen_t *salenp);
void Getsockname(int fd,struct sockaddr *sa,socklen_t *salenp);
void Getsockopt(int fd,int level,int optname,void *optval,socklen_t *optlenp);
void Listen(int fd,int backlog);
int Poll(struct pollfd *,unsigned long nfds,int timeout);
ssize_t Recv(int fd,void *ptr,size_t nbytes,int flags);
int Socket(int family,int type,int proto);
void Socketpair(int family,int type,int proto,int *fd);

// unixdomain : use stream pipe to tansport fd
ssize_t Read_fd(int fd, void *ptr, size_t nbytes, int *recvfd);
ssize_t Write_fd(int fd, void *ptr, size_t nbytes, int sndfd);
ssize_t write_fd(int fd, void *ptr, size_t nbytes, int sndfd);





#endif    /* util.h*/
