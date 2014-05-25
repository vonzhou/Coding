#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<errno.h>

char path[20] = "/dev/scull0";
char buf[128];
int main(){
	int f = open(path,O_RDWR);
	if(f == -1){
		printf("scull open failed ,errno = %d\n",errno);
		exit(-1);
	}

	printf("Input a str to write to the scull device:\n");
	scanf("%s",buf);
	write(f,buf,sizeof(buf));

	printf("Read the str from the device\n");
	read(f, buf, sizeof(buf));
	printf("result:%s\n",buf);
	
	close(f);
}
