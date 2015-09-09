
#include "../unpipc.h"

// ---------------- fd and file read/write --------------------
int
Open(const char *pathname, int oflag, ...)
{
	int		fd;
	va_list	ap;
	mode_t	mode;

	if (oflag & O_CREAT) {
		va_start(ap, oflag);		/* init ap to final named argument */
		mode = va_arg(ap, va_mode_t);
		if ( (fd = open(pathname, oflag, mode)) == -1)
			err_sys("open error for %s", pathname);
		va_end(ap);
	} else {
		if ( (fd = open(pathname, oflag)) == -1)
			err_sys("open error for %s", pathname);
	}
	return(fd);
}


void
Close(int fd)
{
	if (close(fd) == -1)
		err_sys("close error");
}

void
Dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		err_sys("dup2 error");
}

int
Fcntl(int fd, int cmd, void *arg)
{
	int	n;

	if ( (n = fcntl(fd, cmd, arg)) == -1)
		err_sys("fcntl error");
	return(n);
}

ssize_t
Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t		n;

	if ( (n = read(fd, ptr, nbytes)) == -1)
		err_sys("read error");
	return(n);
}


void
Write(int fd, void *ptr, size_t nbytes)
{
	if (write(fd, ptr, nbytes) != nbytes)
		err_sys("write error");
}

void
Unlink(const char *pathname)
{
	if (unlink(pathname) == -1)
		err_sys("unlink error for %s", pathname);
}
// ------------------- process and thread control ----------------

pid_t
Wait(int *iptr)
{
	pid_t	pid;

	if ( (pid = wait(iptr)) == -1)
		err_sys("wait error");
	return(pid);
}

pid_t
Waitpid(pid_t pid, int *iptr, int options)
{
	pid_t	retpid;

	if ( (retpid = waitpid(pid, iptr, options)) == -1)
		err_sys("waitpid error");
	return(retpid);
}

pid_t
Fork(void)
{
	pid_t	pid;

	if ( (pid = fork()) == -1)
		err_sys("fork error");
	return(pid);
}



void *
Malloc(size_t size)
{
	void	*ptr;

	if ( (ptr = malloc(size)) == NULL)
		err_sys("malloc error");
	return(ptr);
}

void *
Calloc(size_t n, size_t size)
{
	void	*ptr;

	if ( (ptr = calloc(n, size)) == NULL)
		err_sys("calloc error");
	return(ptr);
}

int
Getopt(int argc, char *const *argv, const char *str)
{
	int		opt;

	if ( ( opt = getopt(argc, argv, str)) == '?')
		exit(1);		/* getopt() has already written to stderr */
	return(opt);
}

// -------------- pipe and fifo --------------

void
Pipe(int *fds)
{
	if (pipe(fds) < 0)
		err_sys("pipe error");
}

void
Mkfifo(const char *pathname, mode_t mode)
{
	if (mkfifo(pathname, mode) == -1)
		err_sys("mkfifo error for %s", pathname);
}


// ---------------- system v msg queue ------------
int
Msgget(key_t key, int flag)
{
	int		rc;

	if ( (rc = msgget(key, flag)) == -1)
		err_sys("msgget error");
	return(rc);
}

void
Msgctl(int id, int cmd, struct msqid_ds *buf)
{
	if (msgctl(id, cmd, buf) == -1)
		err_sys("msgctl error");
}

void
Msgsnd(int id, const void *ptr, size_t len, int flag)
{
	if (msgsnd(id, ptr, len, flag) == -1)
		err_sys("msgsnd error");
}

ssize_t
Msgrcv(int id, void *ptr, size_t len, int type, int flag)
{
	ssize_t	rc;

	if ( (rc = msgrcv(id, ptr, len, type, flag)) == -1)
		err_sys("msgrcv error");
	return(rc);
}


// ---------------- system v share memory -----------------


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