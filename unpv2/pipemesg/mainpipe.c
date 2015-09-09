#include	"mesg.h"

void	client(int, int), server(int, int);

int
main(int argc, char **argv)
{
	int		pipe1[2], pipe2[2];
	pid_t	childpid;

	Pipe(pipe1);	/* create two pipes */
	Pipe(pipe2);

	if ( (childpid = Fork()) == 0) {		
		/* child: write pipe2, read pipe1 */
		Close(pipe1[1]);
		Close(pipe2[0]);

		server(pipe1[0], pipe2[1]);
		exit(0);
	}
	/* parent , read pipe2 , write pipe1*/
	Close(pipe1[0]);
	Close(pipe2[1]);

	client(pipe2[0], pipe1[1]);

	Waitpid(childpid, NULL, 0);		/* wait for child to terminate */
	exit(0);
}

