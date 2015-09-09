#include	"mesg.h"

ssize_t
mesg_send(int fd, struct mymesg *mptr)
{
	int res = write(fd, mptr, MESGHDRSIZE + mptr->mesg_len);
	// printf("mesg_send: send len= %d\n", res);
	return res;
}

void
Mesg_send(int fd, struct mymesg *mptr)
{
	ssize_t	n;

	if ( (n = mesg_send(fd, mptr)) != (MESGHDRSIZE + mptr->mesg_len))
		err_quit("mesg_send error");
}
