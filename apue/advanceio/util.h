#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>   // pipe(),


#define MAXLINE 50


void err_exit(int errno,const char *fmt,...);
void err_quit(const char *fmt,...);
void err_sys(const char *fmt,...);
void err_dump(const char *fmt,...);



typedef void Sigfunc(int);  /*for signal handlers*/
Sigfunc *signal(int signo,Sigfunc *func);
void pr_mask(const char *str);
void pr_exit(int status);












