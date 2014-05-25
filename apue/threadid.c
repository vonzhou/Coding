#include "util.h"
#include<pthread.h>

pthread_t ntid;

void
printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	//之所以打印16进制，便于pthread_t是结构体的话看地址；
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
	  (unsigned int)tid, (unsigned int)tid);
}

void *
thr_fn(void *arg)
{
	printids("new thread: ");
	return((void *)0);
}

int
main(void)
{
	int		err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if (err != 0)
		err_quit("can't create thread: %s\n", strerror(err));
	printids("main thread:");
	sleep(1);//确保会执行新线程
	exit(0);
}

