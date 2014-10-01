
/**
 * 在信号处理函数中调用不可重入函数
 */
#include "util.h"
#include <pwd.h>

static void
my_alarm(int signo){
    struct passwd*rootptr;
    printf("in signal handler\n");
    if ((rootptr = getpwnam("de15")) == NULL)
        err_sys("getpwnam(de15) error");
    alarm(1);
}

int
main(void){
    struct passwd*ptr;

    signal(SIGALRM, my_alarm);
    alarm(1);
    for ( ; ; ) {
        if ((ptr = getpwnam("vonzhou")) == NULL)
            err_sys("getpwnam error");
        if (strcmp(ptr->pw_name, "vonzhou") != 0)
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
    }
}

