#include <stdio.h>

#include "list.h"

void free_int(void *data){
	free(data);
}

int main(){
	int i;
	int arr[10];
	List *list;
	for(i = 0; i< 10; i++)
		arr[i] = 3 * i + 1;

	list = (List *)malloc(sizeof(List));
	if(list == NULL)
		return -1;

	for(i = 0; i< 10; i++)
		list_ins_next(list, NULL, (void *)(arr + i));


}
