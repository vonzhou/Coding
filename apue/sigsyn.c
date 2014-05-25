#include "util.h"

static void charatatime(char *str);
static volatile sig_atomic_t sigflag;
static sigset_t newmask,zeromask,oldmask;
void TELL_WAIT(void);
void WAIT_PARENT(void);
void TELL_CHILD(pid_t pid);

static void
sig_usr(int signo){
	sigflag = 1;
}

int 
main(void){
	pid_t pid;
	TELL_WAIT();
	if((pid = fork()) < 0){
		err_sys("fork error");
	}else if(pid == 0){
		WAIT_PARENT();
		// let parent goes first;
		charatatime("output from child\n");
	}else{
		charatatime("output from parent\n");
		TELL_CHILD(pid);
	}

	exit(0);
}

static void
charatatime(char *str){
	char *ptr;
	int c;
	setbuf(stdout,NULL);
	for(ptr=str;(c = *ptr++) != 0;)
		putc(c,stdout);
}

void TELL_WAIT(void){
	if(signal(SIGUSR1,sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR1) error");
	if(signal(SIGUSR2,sig_usr) == SIG_ERR)
		err_sys("signal(SIGUSR2) error");
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGUSR1);
	sigaddset(&newmask,SIGUSR2);
	//block sigusr1,2 and save current signal mask;
	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
		err_sys("SIG_BLOCK error");
}

void WAIT_PARENT(void){
	while(sigflag == 0)
		sigsuspend(&zeromask);
	sigflag = 0;
	// reset signal mask to original value;
	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
		err_sys("SIG_SETMASK error");
}

void
TELL_CHILD(pid_t pid){
	kill(pid,SIGUSR1);
}
