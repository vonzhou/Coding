#include "util.h"

int main(){
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.4.135");
	addr.sin_port = htons(13);

	printf("%s\n",Sock_ntop((const struct sockaddr *)&addr,sizeof(addr)));
	return 0;
}
