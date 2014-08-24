#include <stdio.h>

void show(int c[12][31]){


}


int main(){
	int calendar[12][31];
	int *p;
	int i;

	p = calendar[4];
	printf("%d\n", sizeof(p));   // 8
	printf("%d\n", sizeof(calendar[4]));  // 31*4 = 124

	*(p+7) = 90;
	int (*monthp)[31];  // pointer to array
	monthp = calendar;
	printf("%d\n",*( (int *)(monthp + 4) + 7));
	return 0;
}
