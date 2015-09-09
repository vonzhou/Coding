#include	"unpipc.h"

void
client(int readfd, int writefd)
{
	size_t	len;
	ssize_t	n;
	char	buff[MAXLINE];

		/* read pathname */
	Fgets(buff, MAXLINE, stdin);
	len = strlen(buff);		/* fgets() guarantees null byte at end */
	if (buff[len-1] == '\n')
		len--;				/* delete newline from fgets() */

		/* write pathname to IPC channel */
	Write(writefd, buff, len);

		/* read from IPC, write to standard output */
	while ( (n = Read(readfd, buff, MAXLINE)) > 0)
		Write(STDOUT_FILENO, buff, n);
}
