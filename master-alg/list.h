#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>

//elem structure
typedef struct ListElmt_ {
	void *data;
	struct ListElmt_ *next;
}ListElmt;

// link list
typedef struct List_{
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	ListElmt *head;
	ListElmt *tail;
}List;

void list_init(List *list, void (*destroy)(void *data));
void list_destroy(List *list);
int list_ins_next(List *list, ListElmt *element, const void *data);
int list_rem_next(List *list, ListElmt *element, void **data);
#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list,elem) ((list)->head == (elem) ? 1:0)
#define list_is_tail(list,elem) ((list)->tail == (elem) ? 1:0)
#define list_data(elem) ((elem)->data)
#define list_next(elem) ((elem)->next)


#endif // LIST_H_
