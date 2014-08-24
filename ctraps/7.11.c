#include <stdio.h>
#include <stdlib.h>


void printnum(long n, void (*p)()){
	if(n < 0){
		(*p)('-');
		n = -n;
	}

	if(n >= 10)
		printnum(n/10, p);

	(*p)((int)(n % 10) + '0');

}

void func(char c){
	printf("%c\n",c);
}

int main(){
	long x = 145;
	printnum(145, (void (*)())func);   // clever !!!!!

	return 0;
}
