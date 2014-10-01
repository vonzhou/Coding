

#include "util.h"

static void sig_alrm(int);

int
main(void)
{
    int n;
    char line[MAXLINE];
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        err_sys("signal(SIGALRM) error");
    alarm(10);
    if ((n = read(STDIN_FILENO, line, MAXLINE)) < 0)
        err_sys("read error");
    alarm(0);
    write(STDOUT_FILENO, line, n);
    exit(0);
}

static void
sig_alrm(int signo)
{
        /* nothing to do, just return to interrupt the read */
}
/*
 vonzhou@de15:~/Coding/apue/signals$ ./a.out
 read error: Interrupted system call (如果长时间不输入，则发现系统调用被中断)
 vonzhou@de15:~/Coding/apue/signals$ ./a.out
 oewutjowerjtlewrt
 oewutjowerjtlewrt
 vonzhou@de15:~/Coding/apue/signals$ 
*/



