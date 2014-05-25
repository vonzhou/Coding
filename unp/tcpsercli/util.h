#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/un.h>
#include<poll.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>



#define MAXLINE 80
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) //创建的文件默认访问权限


//IO process;
void str_echo(int);
void  Writen(int fd,void *buf,size_t  n);
int Readn(int fd,void *buf,size_t n);
void str_cli(FILE * fp,int fd);
ssize_t Readline(int fd,void *,size_t); //注意返回的是有符号长度；



//进程相关的；
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








