#include "util.h"
#include<setjmp.h>
#include<time.h>

static void sig_usr(int),sig_alrm(int);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjmp;

int 
main(void){
	if(signal(SIGUSR1,sig_usr) == SIG_ERR)
		err_sys("register signal SIGUSR1 error");
	if(signal(SIGALRM,sig_alrm) == SIG_ERR)
		err_sys("register signal SIGALRM error");
	
	pr_mask("starting main:");
	
	if(sigsetjmp(jmpbuf,1)){
		pr_mask("ending main:");
		exit(0);
	}
	
	canjmp = 1;// now sigsetjmp is ok ,can jmp there
	for(;;)
		pause();
}

static void
sig_usr(int signo){
	time_t starttime;
	if(canjmp == 0)
		return;//not prepare well,so ignore it ;
	pr_mask("starting sig_usr:");
	alarm(3); // SIGALRM in 3 sec
	starttime = time(NULL);
	for(;;)
		if(time(NULL) > starttime + 5)	
			break;
	pr_mask("ending sig_usr:");
	
	canjmp = 0;
	siglongjmp(jmpbuf,1);
}

static void
sig_alrm(int signo){
	pr_mask("in sig_alrm:");
}










