
#include<signal.h>
#include<errno.h>
/**
 * 假设把 sigset_t 视为整数，各种位操作
 */
/* <signal.h> usually defines NSIG to include signa l number 0 */
#define SIGBAD(signo)((signo) <= 0 || (signo) >= NSIG)

int sigaddset(sigset_t *set, int signo)
{
    if (SIGBAD(signo)) { errno = EINVAL; return(-1); }
    
    *set |= 1 << (signo - 1);/* turn bit on */
    return(0);
}       

int
sigdelset(sigset_t *set, int signo)
{
    if (SIGBAD(signo)) { errno = EINVAL; return(-1); }
    *set &= ~(1 << (signo - 1));/* turn bit off */
    retur   n(0);
}

int
sigismember(const sigset_t *set, int signo)
{
    if (SIGBAD(signo)) { errno = EINVAL; return(-1); }
    return((*set & (1 << (signo - 1))) != 0);
}

