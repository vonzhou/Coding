#include<stdio.h>

char *echo(){
	char str[] = "vonzhou";  // This is wrong, after teh func returned ,it dead
	//char *str = "vonzhou";
	static str2[] = "hello"; // can work
	printf("-----\n");
	return str;
}

main(){
	char *p;
	p = echo();
	printf("return: %s\n",p);
	return 0;
}
