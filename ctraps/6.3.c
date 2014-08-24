#include <stdio.h>
#include <math.h>

#define assert(e) \
	{ if(!(e)) assert_error(__FILE__, __LINE__); }

void assert_error(char *filename, int line){
	printf("Error ouccurred in %s at line:%d\n", filename, line);
}


int main(){
	int flag = 1;
	int y = 8;
	if(flag)
		assert(y > 0)
	else printf("hhhhhhhhh\n");
	printf("%f\n", sqrt(y));
//	printf("test, %s--%d\n", __FILE__, __LINE__);

	return 0;
}
