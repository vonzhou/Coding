#include <stdio.h>
#include <stdlib.h>

int main(){
	int a = 10;
	int b = 100;
	int *pa = &a;
	int *pb = &b;

	pa ^= pb;
	pb ^= pa;
	pa ^= pb;

	printf("a = %d, b = %d\n", *pa, *pb);
	
	brk(0);
}
