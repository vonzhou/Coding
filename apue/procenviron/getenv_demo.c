#include <stdio.h>
#include <stdlib.h>

int main(){

	printf("HOME - %s\n", getenv("HOME"));
	printf("PATH - %s\n", getenv("PATH"));
	printf("LOGNAME - %s\n", getenv("LOGNAME"));
	printf("PWD - %s\n", getenv("PWD"));
	printf("TERM - %s\n", getenv("TERM"));

	return 0;
}


























