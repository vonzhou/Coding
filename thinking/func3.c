#include <stdio.h>

int *func(int n){

	int x = n *n;
	static int a[] = {1,3,4,5,7};
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
	func2(2);
	printf("%d\n", a[0]);

	return 0;
}
