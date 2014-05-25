#include "util.h"

int
my_open(const char *pathname, int mode){
	int fd, sockfd[2], status;
	pid_t pid;
	char c, argsockfd[10], argmode[10];

	Socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd);

	if((pid = Fork()) == 0){
		// child process
		Close(sockfd[0]); //close the read end
		snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
		// because the execl need string parameters
		snprintf(argmode, sizeof(argmode), "%d", mode);
		execl("./openfile","openfile",argsockfd,pathname,argmode,(char *)NULL);
		
		err_sys("execl error"); // if get here then something wrong;
	}
	// parent process- wait for the child to terminate
	Close(sockfd[1]); // close the write end
	
	Waitpid(pid, &status, 0);
	if(WIFEXITED(status) == 0)
		err_quit("child did not terminate normally");
	if((status = WEXITSTATUS(status)) == 0)
		Read_fd(sockfd[0], &c, 1, &fd);
	else{
		errno = status;
		fd = -1;
	}
	
	Close(sockfd[0]);
	return fd;
}
