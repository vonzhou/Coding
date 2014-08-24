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
void show(int *a, int len){
	int i;
	for(i = 0; i< len ;i++)
		printf("%d  ",a[i]);
	printf("\n");
}
int main(){
	int n = 7;
	int a[] = {12,45,-12, 5, 89, 100, 0};

	insert_sort(a, 0 , n);
	show(a,n);
	return 0;
}



