#include <stdlib.h>
#include <string.h>

#include "list.h"

void list_init(List *list, void (*destroy)(void *data)){
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
	return;
}

void list_destroy(List *list){
	void *data;
	
	//remove each element from head
	while(list_size(list) > 0){
		if(list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL)
			list->destroy(data);
	}

}

int list_ins_next(List *list, ListElmt *elem,const void *data){
	ListElmt *new;
	if((new = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
		return -1;   	
	new->data = (void *)data;
	if(elem == NULL){
		//insertion at the head of list
		if(list_size(list) == 0)
			list->tail = new;
		new->next = list->head;  // NULL
		list->head = new;
	}else{
		//other case
		if(elem->next == NULL)//insert to the last
			list->tail = new;
		new->next = elem->next;
		elem->next = new;
	}
	list->size ++;

	return 0;
}

//remove the element after elem, data is the value removed.
int list_rem_next(List *list, ListElmt *elem, void **data){
	ListElmt *old;
	if(list_size(list) == 0)
		return -1;

	if(elem == NULL){
		//remove from the heading 
		*data = list->head->data;
		old = list->head;
		list->head = list->head->next;
		
		//deal with the tail pointer
		if(list_size(list) == 1) // no members now
			list->tail = NULL;
	}else{
		if(elem->next == NULL)//no element after 
			return -1;
		*data = elem->next->data;
		old = elem->next;
		elem->next = elem->next->next;
		
		if(elem->next == NULL)
			list->tail = elem;
	}

	free(old);
	list->size --;

	return 0;
}
