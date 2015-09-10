#include	"mesg.h"

ssize_t
mesg_send(int id, struct mymesg *mptr)
{
	return(msgsnd(id, &(mptr->mesg_type), mptr->mesg_len, 0));
}

// just send a msg
void
Mesg_send(int id, struct mymesg *mptr)
{
	ssize_t	n;

	if ( (n = msgsnd(id, &(mptr->mesg_type), mptr->mesg_len, 0)) == -1)
		err_sys("mesg_send error");
}
