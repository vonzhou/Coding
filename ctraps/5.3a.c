#include <stdio.h>
#include <stdlib.h>

void func(){
	int c;

	//static char buf[BUFSIZ];
	setbuf(stdout, malloc(BUFSIZ));
	printf("BUFSIZ : %d\n", BUFSIZ);
	while((c = getchar()) != EOF)
		putchar(c);

}


int main(){
	func();
	printf("---------in  main---------\n");
	return 0;
}
