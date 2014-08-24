#include <stdio.h>

int days1[] = {31, 28, 31, 30, 31, 30, 
			31, 31, 30, 31, 30, 31};
int days[] = {31, 28, 31, 30, 31, 30, 
			31, 31, 30, 31, 30, 31,};


int main(){
	int i, sum=0;
	for(i = 0; i< 12; i++)
		sum += days[i];
	days[30] = 999;
	days1[12] = 888;
	printf("%d\n", sum);

	return 0;
}
