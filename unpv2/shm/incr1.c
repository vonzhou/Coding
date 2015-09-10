#include	"../unpipc.h"

#define	SEM_NAME	"mysem"

int		count = 0;

int
main(int argc, char **argv)
{
	int		i, nloop;
	sem_t	*mutex;

	if (argc != 2)
		err_quit("usage: incr1 <#loops>");
	nloop = atoi(argv[1]);

	/* create, initialize, and unlink semaphore */
	char *ipc_name = Px_ipc_name(SEM_NAME);
	// printf("Posix IPC name is %s\n", ipc_name);
	// mutex = Sem_open(ipc_name, O_CREAT | O_EXCL, FILE_MODE, 1);
	// Sem_unlink(ipc_name);

	// sem_open error for /tmp/mysem: No such file or directory
	mutex = Sem_open(SEM_NAME, O_CREAT | O_EXCL, FILE_MODE, 1);
	//Sem_unlink(SEM_NAME);

	system("ls /dev/shm/");
	system("ipcs -s");

	setbuf(stdout, NULL);	/* stdout is unbuffered */
	if (Fork() == 0) {		/* child */
		for (i = 0; i < nloop; i++) {
			Sem_wait(mutex);
			printf("child: %d\n", count++);
			Sem_post(mutex);
		}
		exit(0);
	}

	/* parent */
	for (i = 0; i < nloop; i++) {
		Sem_wait(mutex);
		printf("parent: %d\n", count++);
		Sem_post(mutex);
	}
	exit(0);
}
