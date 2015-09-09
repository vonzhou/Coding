#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>


int main(){

	int childB, childC;
	int pipefds[2];
	char *args1[] = {"//usr/bin/wc", NULL};
	char *args2[] = {"/bin/ls", "-l", NULL};

	//=======Process A======
	pipe(pipefds);

	if(!(childB = fork())){
		//======== Process B ========
		close(pipefds[1]);// close write pipe end
		// redirect stdin
		close(0);
		dup2(pipefds[0], 0);
		close(pipefds[0]);

		// execute the target
		execve("/usr/bin/wc", args1, NULL);
		printf("pid %d: I got here, sth is WRONG!\n", getpid());
	}
	// Process A continue
	close(pipefds[0]);

	if(!(childC = fork())){
		//======== Process C ========
		//redirect stdout
		close(1);
		dup2(pipefds[1], 1);
		close(pipefds[1]);

		// execute the target
		execve("/bin/ls", args2, NULL);
		//ERROR: If run to here 
		printf("pid %d: I got here, sth is WRONG!\n", getpid());
	}

	close(pipefds[1]);
	wait4(childB, NULL, 0, NULL);
	printf("%s\n", "OVER!");

	return 0;
}