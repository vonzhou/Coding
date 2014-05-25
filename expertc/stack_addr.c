#include<stdio.h>

static int x = 1;
int y[100];

main(){
	int i;
	int y = 2;
	printf("The stack top is near %p\n",&i);
	printf("The stack change %p\n",&y);
	printf("The data section is near %p\n",&x);
	printf("The BSS is near %p\n",y);
	return 0;
}
