#include "util.h"

int
main(void){
	int fd[2];
	int n;
	pid_t pid;
	char line[MAXLINE];
	
	if(pipe(fd) < 0)
		err_sys("pipe error");
	if((pid = fork()) < 0)
		err_sys("fork error");
	else if(pid == 0){
		//child
		close(fd[1]);
		n = read(fd[0],line,MAXLINE);
		write(STDOUT_FILENO,line,n);
	}else{
		//parent
		close(fd[0]);
		write(fd[1],"hello vonzhou\n",14);
	}
	
	exit(0);
}
