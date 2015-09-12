/* Use standard echo server; baseline measurements for nonblocking version */
#include	"../unp.h"

//vonzhou: for SIGPIPE
void sig_pipe(int signo){
	printf("SIGPIPE caught in client, signo=%d, pid=%d\n", signo, getpid());
	exit(-1);
}


int
main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr;

	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	// handle SIGPIPE
	Signal(SIGPIPE, sig_pipe);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	str_cli(stdin, sockfd);		/* do it all */

	exit(0);
}
