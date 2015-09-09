#include <stdio.h>
#include <stdlib.h>

// What can "int *p" be used for ??
int main(){
	int *p1;
	int *p2;
	int *p3;
	int *p4;

	int a  =1;
	p1 = &a; //case1: pointer to int

	int b[10];
	p2 = b; // case2: pointer to a one dimension arr

	p3 = malloc( 10 * sizeof(int)); // case3: dynamic arr
	p3[3] = 99;
	free(p3);

	int c[3][4];
	p4 = c; //  warning: assignment from incompatible pointer type [enabled by default]
	int (*p5)[4];
	p5 = c;   // OK!!
	p5[1][0] = 100;
	printf("%d\n", c[1][0]);

	printf("%s\n", "Hello T!");


}