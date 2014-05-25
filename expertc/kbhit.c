#include <sys/ioctl.h>

int kbhit(){
	int i;
	ioctl(0, FIONREAD, &i);
	return i;
}

main(){
	int i = 0;
	int c = '';
	system("stty raw -echo");
	printf("enter 'q' to quit \n");
	for(; c !='q'; i++){
		if(kbhit()){
			c = getchar();
			printf(" \n got %c, on iteration %d", c, i);
		}
	}
	system("stty cooked echo");
}
