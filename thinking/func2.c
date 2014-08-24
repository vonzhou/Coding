#include <stdio.h>
#include <stdlib.h>

int *func(int n){

	int x = n *n;
	int *a = (int *)malloc(5 * sizeof(int));
	a[0] = x;
	return a;
}

void func2(){
	int a = 1;
	int b = 78;
	printf("%d vonzhou jjjj.\n",a);
}

int main(){
	int n = 3;
	int *a = func(3);
	func(2);
	printf("%d\n", a[0]);
	
	free(a);
	return 0;
}
