#include "util.h"
static void sig_int(int);

int
main(void){
	sigset_t newmask,oldmask,waitmask;
	
	pr_mask("program start:");
	
	if(signal(SIGINT,sig_int) == SIG_ERR)
		err_sys("register signal SIGINT error");
	sigemptyset(&waitmask);
	sigaddset(&waitmask,SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);
	
	// block SIGINT and save current signal mask;
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
		err_sys("SIG_BLOCK SIGINT error");

	// here is the Critical region of code ....
	
	pr_mask("in critical region:");

	//pause,only SIGUSR1 can wake this suspend..
	if(sigsuspend(&waitmask) != -1)
		err_sys("sigsuspend error");

	pr_mask("after return from sigsuspend:");
	
	//Reset the signal mask
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
		err_sys("SIG_SETMASK error"); 

	//continue other processing....
	pr_mask("program exit: ");
	exit(0);
}

static void
sig_int(int signo){
	pr_mask("\nin sig_int:");
}
