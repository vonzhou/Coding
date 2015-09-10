#include	"mesg.h"

void
server(int readfd, int writefd)
{
	FILE	*fp;
	char	*ptr;
	pid_t	pid;
	ssize_t	n;
	struct mymesg	mesg;
	// iterate server
	for ( ; ; ) {
		/* read pathname from IPC channel */
		mesg.mesg_type = 1; // need type 1 (client request)
		if ( (n = Mesg_recv(readfd, &mesg)) == 0) {
			err_msg("pathname missing");
			continue;
		}
		mesg.mesg_data[n] = '\0';	/* null terminate pathname */

		if ( (ptr = strchr(mesg.mesg_data, ' ')) == NULL) {
			err_msg("bogus request: %s", mesg.mesg_data);
			continue;
		}

		*ptr++ = 0;			/* null terminate PID, ptr = pathname */
		pid = atol(mesg.mesg_data);
		mesg.mesg_type = pid;	/* for messages back to client */

		if ( (fp = fopen(ptr, "r")) == NULL) {
			/* error: must tell client */
			snprintf(mesg.mesg_data + n, sizeof(mesg.mesg_data) - n,
					 ": can't open, %s\n", strerror(errno));
			mesg.mesg_len = strlen(ptr);
			// 
			memmove(mesg.mesg_data, ptr, mesg.mesg_len);
			Mesg_send(writefd, &mesg);
	
		} else {
			/* fopen succeeded: copy file to IPC channel */
			while (Fgets(mesg.mesg_data, MAXMESGDATA, fp) != NULL) {
				// every line is a msg
				mesg.mesg_len = strlen(mesg.mesg_data);
				Mesg_send(writefd, &mesg);
			}
			Fclose(fp);
		}
	
		/* send a 0-length message to signify the end */
		mesg.mesg_len = 0;
		Mesg_send(writefd, &mesg);
	}
}
