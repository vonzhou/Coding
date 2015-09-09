/* System V IPC wrapper functions

*/



#include "../unpipc.h"

int
Getopt(int argc, char *const *argv, const char *str)
{
	int		opt;

	if ( ( opt = getopt(argc, argv, str)) == '?')
		exit(1);		/* getopt() has already written to stderr */
	return(opt);
}

key_t
Ftok(const char *pathname, int id)
{
	key_t	key;

	if ( (key = ftok(pathname, id)) == -1)
		err_sys("ftok error for pathname \"%s\" and id %d", pathname, id);
	return(key);
}

int
Shmget(key_t key, size_t size, int flags)
{
	int		rc;

	if ( (rc = shmget(key, size, flags)) == -1)
		err_sys("shmget error");
	return(rc);
}

void *
Shmat(int id, const void *shmaddr, int flags)
{
	void	*ptr;

	if ( (ptr = shmat(id, shmaddr, flags)) == (void *) -1)
		err_sys("shmat error");
	return(ptr);
}

void
Shmdt(const void *shmaddr)
{
	if (shmdt(shmaddr) == -1)
		err_sys("shmdt error");
}

void
Shmctl(int id, int cmd, struct shmid_ds *buff)
{
	if (shmctl(id, cmd, buff) == -1)
		err_sys("shmctl error");
}