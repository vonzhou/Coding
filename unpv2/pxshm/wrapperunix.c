
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

off_t
Lseek(int fd, off_t offset, int whence)
{
	off_t	pos;

	if ( (pos = lseek(fd, offset, whence)) == (off_t) -1)
		err_sys("lseek error");
	return(pos);
}

long
Fpathconf(int fd, int name)
{
	long	val;

	errno = 0;		/* in case fpathconf() does not change this */
	if ( (val = fpathconf(fd, name)) == -1) {
		if (errno != 0)
			err_sys("fpathconf error");
		else
			err_sys("fpathconf: %d not defined", name);
	}
	return(val);
}

void
Fstat(int fd, struct stat *ptr)
{
	if (fstat(fd, ptr) == -1)
		err_sys("fstat error");
}



void
Ftruncate(int fd, off_t length)
{
	if (ftruncate(fd, length) == -1)
		err_sys("ftruncate error");
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

long
Pathconf(const char *pathname, int name)
{
	long	val;

	errno = 0;		/* in case pathconf() does not change this */
	if ( (val = pathconf(pathname, name)) == -1) {
		if (errno != 0)
			err_sys("pathconf error");
		else
			err_sys("pathconf: %d not defined", name);
	}
	return(val);
}

long
Sysconf(int name)
{
	long	val;

	errno = 0;		/* in case sysconf() does not change this */
	if ( (val = sysconf(name)) == -1) {
		if (errno != 0)
			err_sys("sysconf error");
		else
			err_sys("sysconf: %d not defined", name);
	}
	return(val);
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

// ----------------- semaphore ----------------
sem_t *
Sem_open(const char *pathname, int oflag, ...)
{
	sem_t	*sem;
	va_list	ap;
	mode_t	mode;
	unsigned int	value;

	if (oflag & O_CREAT) {
		va_start(ap, oflag);		/* init ap to final named argument */
		mode = va_arg(ap, va_mode_t);
		value = va_arg(ap, unsigned int);
		if ( (sem = sem_open(pathname, oflag, mode, value)) == SEM_FAILED)
			err_sys("sem_open error for %s", pathname);
		va_end(ap);
	} else {
		if ( (sem = sem_open(pathname, oflag)) == SEM_FAILED)
			err_sys("sem_open error for %s", pathname);
	}
	return(sem);
}

void
Sem_close(sem_t *sem)
{
	if (sem_close(sem) == -1)
		err_sys("sem_close error");
}

void
Sem_unlink(const char *pathname)
{
	if (sem_unlink(pathname) == -1)
		err_sys("sem_unlink error");
}

void
Sem_init(sem_t *sem, int pshared, unsigned int value)
{
	if (sem_init(sem, pshared, value) == -1)
		err_sys("sem_init error");
}

void
Sem_destroy(sem_t *sem)
{
	if (sem_destroy(sem) == -1)
		err_sys("sem_destroy error");
}

void
Sem_wait(sem_t *sem)
{
	if (sem_wait(sem) == -1)
		err_sys("sem_wait error");
}

int
Sem_trywait(sem_t *sem)
{
	int		rc;

	if ( (rc = sem_trywait(sem)) == -1 && errno != EAGAIN)
		err_sys("sem_trywait error");
	return(rc);
}

/* include Sem_post */
void
Sem_post(sem_t *sem)
{
	if (sem_post(sem) == -1)
		err_sys("sem_post error");
}
/* end Sem_post */

void
Sem_getvalue(sem_t *sem, int *valp)
{
	if (sem_getvalue(sem, valp) == -1)
		err_sys("sem_getvalue error");
}


int
Semget(key_t key, int nsems, int flag)
{
	int		rc;

	if ( (rc = semget(key, nsems, flag)) == -1)
		err_sys("semget error");
	return(rc);
}

void
Semop(int id, struct sembuf *opsptr, size_t nops)
{
	if (semop(id, opsptr, nops) == -1)
		err_sys("semctl error");
}

int
Semctl(int id, int semnum, int cmd, ...)
{
	int		rc;
	va_list	ap;
	union semun	arg;

	if (cmd == GETALL || cmd == SETALL || cmd == SETVAL ||
		cmd == IPC_STAT || cmd == IPC_SET) {
		va_start(ap, cmd);		/* init ap to final named argument */
		arg = va_arg(ap, union semun);
		if ( (rc = semctl(id, semnum, cmd, arg)) == -1)
			err_sys("semctl error");
		va_end(ap);
	} else {
		if ( (rc = semctl(id, semnum, cmd)) == -1)
			err_sys("semctl error");
	}
	return(rc);
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

// ----------------- memory map -----------------
void *
Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset)
{
	void	*ptr;

	if ( (ptr = mmap(addr, len, prot, flags, fd, offset)) == MAP_FAILED)
		err_sys("mmap error");
	return(ptr);
}

void
Munmap(void *addr, size_t len)
{
	if (munmap(addr, len) == -1)
		err_sys("munmap error");
}



int
Shm_open(const char *pathname, int oflag, mode_t mode)
{
	int		fd;

	if ( (fd = shm_open(pathname, oflag, mode)) == -1)
		err_sys("shm_open error for %s", pathname);
	return(fd);
}


void
Shm_unlink(const char *pathname)
{
	if (shm_unlink(pathname) == -1)
		err_sys("shm_unlink error");
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