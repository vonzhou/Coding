// prag: 8-6
#include "util.h"

static void charatatime(char *);

int main(void){
	pid_t	pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) {
		charatatime("output from child\n");
	} else {
		charatatime("output from parent\n");
	}
	exit(0);
}

static void charatatime(char *str){
	char	*ptr;
	int		c;

	// 标准输出设置为不带缓冲，每个字符输出都会调用一次write
	setbuf(stdout, NULL);			/* set unbuffered */
	for (ptr = str; (c = *ptr++) != 0; )
		putc(c, stdout);
}

