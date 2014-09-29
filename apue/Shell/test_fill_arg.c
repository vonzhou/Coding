
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_argv[100];


int main(){

	char *s = "gcc -o hello hello.c";
	fill_argv(s);
	printf("%s\n", s);
	
	return 0;
}


