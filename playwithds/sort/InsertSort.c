#include "sort.h"

void InsertSort(SqList *L){
	int i, j;
	for(i = 2; i <= L->length; i++){
		if(L->r[i] < L->r[i-1]){
			// 需要在有序子表中找到自己合适的位置
			L->r[0] = L->r[i];
			for(j = i-1; L->r[j] > L->r[0]; j--)
				L->r[j+1] = L->r[j];
			L->r[j+1] = L->r[0];
		}	
	}
}

int main(){
	SqList list;
	SqList *L = &list;
	int data[] = {0,34,4,5,32,6,11,10};
	L->r = data;
	L->length = 7;
	InsertSort(L);
	show(L);
}





































