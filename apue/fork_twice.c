#include "util.h"
#include<sys/wait.h>

int main(void){
	pid_t pid;
	
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0){
		//first child
		if((pid = fork()) < 0)
			err_sys("fork error");
		else if(pid > 0)
			exit(0); // parent from second fork == first child ,first child exit;
		//we are the second child,our parent become init as soon as
		//our real parent calls exit() int the statement above;]	
		//continue executing,when we're done,init will reap our status
		sleep(2); //so that the first child been exited;
		printf("second child,parent pid = %d\n",getppid());
		exit(0);
	}

	if(waitpid(pid,NULL,0) != pid)
		err_sys("waitpid error");
	
	//we're the original process,continue executing,
	//knowing that we're not the parent of the second child
	exit(0);
}
