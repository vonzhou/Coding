#include <stdio.h>

int less(int a, int b){
	if(a < b)
		return 1;
	return 0;
}

void exch(int *a, int i , int j){
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

void insert_sort(int *a, int low, int high){
	int i,j;
	for(i = low; i < high ; i++){
		for(j = i; j > 0 && less(a[j], a[j-1]); j--)
			exch(a, j, j-1);
	}
}

void shellsort(int *a, int low, int N){ // [2,4)
	int h = 1;
	int i,j;
	// find the max step
	while(h < N/3)
		h = 3*h + 1; // 1, 4, 13, 40, 121

	while(h>=1){
		// invoke insert sort for different step
		for(i = h; i < N; i+=h){
			for(j = i; j > 0 && less(a[j], a[j-h]); j -=h)
				exch(a,j,j-h);
		}
		h = h/3;
	}
}
void show(int *a, int len){
	int i;
	for(i = 0; i< len ;i++)
		printf("%d  ",a[i]);
	printf("\n");
}
int main(){
	int n = 7;
	int a[] = {12,45,-12, 5, 89, 100, 0};

	//insert_sort(a, 0 , n);
	shellsort(a, 0 , n);
	show(a,n);
	return 0;
}



