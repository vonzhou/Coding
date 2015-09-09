#include	"fifo.h"

int
main(int argc, char **argv)
{
	int		readfifo, writefifo;
	size_t	len;
	ssize_t	n;
	char	*ptr, fifoname[MAXLINE], buff[MAXLINE];
	pid_t	pid;

	/* create FIFO with our PID as part of name */
	pid = getpid();
	snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long) pid);
	if ((mkfifo(fifoname, FILE_MODE) < 0) && (errno != EEXIST))
		err_sys("can't create %s", fifoname);

	/* start buffer with pid and a blank */
	snprintf(buff, sizeof(buff), "%ld ", (long) pid);
	len = strlen(buff);
	ptr = buff + len;

	/* read pathname */
	Fgets(ptr, MAXLINE - len, stdin);
	len = strlen(buff);		/* fgets() guarantees null byte at end */

	/* open FIFO to server and write PID and pathname to FIFO */
	writefifo = Open(SERV_FIFO, O_WRONLY, 0);
	Write(writefifo, buff, len);

	/* now open our FIFO; blocks until server opens for writing */
	readfifo = Open(fifoname, O_RDONLY, 0);

	/* read from IPC, write to standard output */
	while ( (n = Read(readfifo, buff, MAXLINE)) > 0)
		Write(STDOUT_FILENO, buff, n);

	Close(readfifo);
	Unlink(fifoname);
	exit(0);
}
