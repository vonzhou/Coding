#include <stdio.h>


int main(){
	int len = 7;
	int arr[7][7][7];
	int arr2[7];
	arr[0][0][7] = 10;
	arr2[7]  =9;
	printf("%d\n",arr[0][0][7]);
	printf("%d\n",arr2[7]);
	return 0;
}
