#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 50

typedef struct {
	int *r;
	int length;
}SqList;

void swap(SqList *L, int i, int j){
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}

void show(SqList *L){
	int i;
	if(L->length <= 0)
		return;
	for(i = 1; i <= L->length; i++)
		printf("%d ", L->r[i]);
	printf("\n");

}
