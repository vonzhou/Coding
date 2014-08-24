//using inline blocks

#include <stdio.h>

int main(){
	printf("%d\n", ({ int n; scanf("%d", &n); n*n;}));	

	return 0;
}
