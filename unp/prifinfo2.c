#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<errno.h>
#include<net/if.h>
#include<string.h>
#include<sys/un.h>   //struct  sockaddr_un
#include<arpa/inet.h> // inet_ntoa();

void get_ifs(int fd);
void print_hw_addr(int fd, const char* if_name);

int main() {
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == fd) {
		perror("socket failed!");
		return -1;
	}

	get_ifs(fd);
	close(fd);
	return 0;
}

void get_ifs(int fd) {
	struct ifreq ifs[16] = {0}; //只是自己的假象，如果希望健壮的话需动态分配，看UNP；
	struct ifconf conf = {sizeof(ifs)};
	int i=0;
	conf.ifc_req = ifs;
	if(-1 == ioctl(fd, SIOCGIFCONF, &conf)) {
		printf("ioctl SIOCGIFCONF error.");
		return;
	}
	if(conf.ifc_len >= sizeof(ifs)) {
		printf("Buffer too small for IOCTL SIOCGIFCONF.");
		return;
	}
	
	int num = conf.ifc_len / sizeof(struct ifreq);
	printf(" #interface entry retrieved: %d \n",num);
	for(i = 0; i < num; ++i) {
		printf( "[ %s ] " ,ifs[i].ifr_name);
		struct sockaddr_in *sai = (struct sockaddr_in*)&ifs[i].ifr_addr;
		printf(" Address: %s ",inet_ntoa(sai->sin_addr));
		print_hw_addr(fd, ifs[i].ifr_name);
		printf("\n");
	}
}

void print_hw_addr(int fd, const char* if_name) {
	struct ifreq req = {0};
	strcpy(req.ifr_name, if_name);
	if(-1 == ioctl(fd, SIOCGIFFLAGS, &req)) {
		printf("Failed IOCTL SIOCGIFFLAGS.");
		return;
	}
	if(req.ifr_flags & IFF_LOOPBACK) {
		printf( " LOOP.");
		return;
	}

	if(-1 == ioctl(fd, SIOCGIFHWADDR, &req)) {
		printf("Failed IOCTL SIOCGIFHWADDR.");
		return;
	}
	unsigned char* raw = (unsigned char*)req.ifr_hwaddr.sa_data;
	printf("MAC addr: %02x:%02x:%02x:%02x:%02x:%02x/n",raw[0], raw[1], raw[2], raw[3], raw[4], raw[5]);
	// 因为TCP/IP中是大端模式，所以先输出低字节；
}

