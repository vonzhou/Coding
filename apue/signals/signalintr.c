#include "util.h"

// will stop all the inttrupted signal,that is sigaction's 
//default behavior ,so deal with the early aspects;
Sigfunc *
signal_intr(int signo, Sigfunc *func)
{
    struct sigaction    act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
    if (sigaction(signo, &act, &oact) < 0)
        return(SIG_ERR);
    return(oact.sa_handler);
}
