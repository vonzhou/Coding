#include <stdio.h>

int main(){
	int n;
	//util reach EOF(ctrl + D) 
	while(~scanf("%d",&n)){
		//logic process
		printf("%d^2 = %d\n", n, n*n);
	}

	// %m print success only if errno = 0
	printf("%m\n");

	
	brk(0);
}
