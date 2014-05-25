#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<errno.h>
#include	<string.h>


int
my_inet_pton(int family, const char *strptr, void *addrptr)
{
    if (family == AF_INET) {
    	struct in_addr  in_val;

        if (inet_aton(strptr, &in_val)) {
            memcpy(addrptr, &in_val, sizeof(struct in_addr));
            return (1);
        }
		return(0);
    }
	errno = EAFNOSUPPORT;
    return (-1);
}

const char *
my_inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const u_char *p = (const u_char *) addrptr;

	if (family == AF_INET) {
		char	temp[INET_ADDRSTRLEN];

		snprintf(temp, sizeof(temp), "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
		if (strlen(temp) >= len) {
			errno = ENOSPC;
			return (NULL);
		}
		strcpy(strptr, temp);
		return (strptr);
	}
	errno = EAFNOSUPPORT;
	return (NULL);
}

int main(){
	char buf[INET_ADDRSTRLEN]={0};
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr = inet_addr("192.168.4.135");
	printf("%s\n",my_inet_ntop(AF_INET,(const void *)&addr.sin_addr,buf,sizeof(buf)));	
//	printf("%s\n",inet_ntop(AF_INET,(const void *)&addr.sin_addr,buf,sizeof(buf)));
	return 0;
}
