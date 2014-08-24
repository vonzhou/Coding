#include "util.h"
#include <pthread.h>

struct foo {
	int a, b, c, d;
};

void
printfoo(const char *s, const struct foo *fp)
{
	printf(s);
	printf("  structure at 0x%x\n", (unsigned)fp);
	printf("  foo.a = %d\n", fp->a);
	printf("  foo.b = %d\n", fp->b);
	printf("  foo.c = %d\n", fp->c);
	printf("  foo.d = %d\n", fp->d);
}

void *
thr_fn1(void *arg)
{
	struct foo	foo = {1, 2, 3, 4};

	printfoo("thread 1:\n", &foo);
	pthread_exit((void *)&foo);
	//这里是自动变量，退出的时候只是告知监听者退出状态码所在的地址，但是里面的内容在函数退出时就变了；
}

void *
thr_fn2(void *arg)
{
	printf("thread 2: ID is %ld\n", pthread_self());//这里最好用长整型；
	pthread_exit((void *)0);
}

int
main(void)
{
	int			err;
	pthread_t	tid1, tid2;
	struct foo	*fp;

	err = pthread_create(&tid1, NULL, thr_fn1, NULL);
	if (err != 0)
		err_quit("can't create thread 1: %s\n", strerror(err));
	err = pthread_join(tid1, (void *)&fp);
	if (err != 0)
		err_quit("can't join with thread 1: %s\n", strerror(err));
	sleep(1);
	printf("parent starting second thread\n");
	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
		err_quit("can't create thread 2: %s\n", strerror(err));
	sleep(1);
	printfoo("parent:\n", fp);
	exit(0);
}
