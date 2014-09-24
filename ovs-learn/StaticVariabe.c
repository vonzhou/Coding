
#include <stdio.h>
#include <stdlib.h>

void func(){
	static int x = 0;
	if(!x){
		x = 1;
		printf("I am got here!\n");
	}
}

int main(){
	func();
	func();
}

























