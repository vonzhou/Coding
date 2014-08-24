#include <stdio.h>
#include <stdlib.h>

int main(){
	int c;

	//static char buf[BUFSIZ];
	setbuf(stdout, malloc(BUFSIZ));
	printf("BUFSIZ : %d\n", BUFSIZ);
	while((c = getchar()) != EOF)
		putchar(c);

	return 0;
}
