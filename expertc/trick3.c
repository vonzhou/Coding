#include <stdio.h>
#include <stdlib.h>

#define offset(TYPE, MEMBER) ((size_t)(&((TYPE *)0)->MEMBER))

int main(){
	struct test{
		int a;
		int b[4];
		int c;
	};
	
	printf("offset a : %lu\n", offset(struct test, a));
	printf("offset b : %lu\n", offset(struct test, b));
	printf("offset c : %lu\n", offset(struct test, c));

	struct test *t = (struct test *)0;
	printf("%d\n", &(t->c));  // right
	printf("%d\n", t->c);  //?but cannot do this, core dump
	

	return 0;
}
