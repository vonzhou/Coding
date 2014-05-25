#include "util.h"
#include<sys/wait.h>

int 
main(void){
	pid_t pid;
	int status;

	if((pid=fork()) < 0)
		err_sys("fork error");
	else if(pid == 0)
		exit(7);// child process exit
	//wait child
	if(wait(&status) != pid)
		err_sys("wait child error");
	pr_exit(status);

	if((pid=fork()) < 0)
                err_sys("fork error");
        else if(pid == 0)
                abort(); // generate SIGABRT;
        
        if(wait(&status) != pid)
                err_sys("wait child error");
        pr_exit(status);

	if((pid=fork()) < 0)
                err_sys("fork error");
        else if(pid == 0)
		status /= 0; // divide by 0 generate SIGFPE;                
        
        if(wait(&status) != pid)
                err_sys("wait child error");
        pr_exit(status);

	exit(0);
}
