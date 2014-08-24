#include <stdio.h>
#include <stdlib.h>


void printnum(long n, void (*p)()){
	if(n < 0){
		printf("n is negative .\n");
		(*p)('-');
		n = -n;
	}

	if(n >= 10)
		printnum(n/10, p);

	(*p)("0123456789"[n % 10]);

}

void func(char c){
	printf("%c\n",c);
}

int main(){
	long x = -145l;
	printnum(x, (void (*)())func);   // clever !!!!!

	return 0;
}
