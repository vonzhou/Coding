#include <stdio.h>

typedef void (*funcptr)(); // typedef makes it clear

void func(){
	printf("entering func.....\n");
}

int main(){
	void *vp = (void *)func;
	(*(void (*)())vp)();
	((void (*)())vp)(); // NB: an abbreviated form
	(*(funcptr)vp)();
	return 0;
}
