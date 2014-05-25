#include <stdio.h>

main(){
	int c;
	system("stty raw");
	c = getchar();
	system("stty cooked");
	return 0;
}
