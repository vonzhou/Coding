#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void sig_usr(int);

int 
main(void){
	if(signal(SIGUSR1,sig_usr) == SIG_ERR){
		printf("cannot catch SIGUSR1!");
        exit(-1);
    }
	
    for(;;)
		pause();
}

static void sig_usr(int signo){
	if(signo == SIGUSR1)
		printf("received SIGUSR1\n");
    else printf("other signals\n");
}
