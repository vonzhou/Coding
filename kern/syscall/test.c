#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
//#ifdef NTDEF
	int n;
	unsigned long i ;
	char buf[10];
	FILE * file = fopen("data.txt", "rw");
	n = fread(buf, 10, 1, file);
//#endif
	//printf("123abc\n");
	for(i=0;i < 1000000; i++){
		//printf("=====\n");
	}
	fclose(file);
	return 0;
}
