#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int
main(int argc, char **argv)
{
	int sockfd;
	socklen_t len;
	struct sockaddr_un addr1, addr2;

	if (argc != 2){
		printf("usage: unixbind <pathname>\n");
		exit(1);
	}

	if((sockfd = socket(PF_UNIX, SOCK_STREAM, 0))<0){
		printf("socket error!\n");
		exit(1);
	}

	unlink(argv[1]);		/* OK if this fails */

	bzero(&addr1, sizeof(addr1));
	addr1.sun_family = PF_UNIX;
	strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path)-1);
	bind(sockfd, (struct sockaddr *) &addr1, SUN_LEN(&addr1));

	len = sizeof(addr2);

	getsockname(sockfd, (struct sockaddr *) &addr2, &len);//获得刚绑定的路径名，值-结果参数；

	printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);
	
	exit(0);
}















