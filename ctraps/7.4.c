#include <stdio.h>

int a=99;

int  A =9;


double square(double x){
	return x*x;
}

int main(){
	char x = (char)130;
	unsigned y = (unsigned)x;
	unsigned char z = (unsigned char )x;
	printf("%x   %x  %x\n",x,y,z);// ffffff82   ffffff82  82
	printf("sizeof char = %d\n", sizeof(char));	
	printf("%c\n", x);
}

