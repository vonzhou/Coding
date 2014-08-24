#if 0

here will not enter into compile
we can move the code we not need now here

#endif

#include<stdio.h>

int  main(){
	int i = 0;
	int arr[] = {[1]=5, [5]=10, [2]=20};
	int arr2[] = {[0 ... 9] = 10, [10 ... 19] = 20, [20 ... 29] = 30};
	for(i = 0; i < 6; i++)
		printf("arr[%d] = %d ,", i, arr[i]);
	printf("\n");
	for(i = 0; i < 30; i++)
		printf("arr2[%d] = %d ,", i, arr2[i]);
	return 0;
}

