
#include<signal.h>
#include<unistd.h>


/**存在的问题是，可能在一个繁忙的系统中调用pause之前超时，
 * 直接调用信号处理程序，pause后如果没有捕捉到其他信号，
 * 该程序将永远被挂起
 */
static void
sig_alrm(int signo)
{
        /* nothing to d o, just return to wake up the pause */
}

unsigned int
sleep1(unsigned int nsecs)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
        return(nsecs);
    alarm(nsecs);/*      start the timer */
    pause();/* next caught signal wakes us up */
    return(alarm(0));/* turn off timer, return unslept time */
}
    
