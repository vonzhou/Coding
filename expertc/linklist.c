#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
} *head;

//sorted link-list
void insert(struct node *new_node){
	struct node *cur = head, *pre = NULL;
	while(cur != NULL && cur->data < new_node->data){
		pre = cur;
		cur = cur->next;
	}

	new_node->next = cur;
	if(pre == NULL)
		head = new_node;
	else
		pre->next = new_node;
}

//use pointer to pointer can make things easier
void insert2(struct node *new_node){
	struct node **linkp = &head;
	while(*linkp !=NULL && (*linkp)->data < new_node->data){
		linkp = &(*linkp)->next;
	}
	
	new_node->next = *linkp;
	*linkp = new_node;
}

void show(){
	struct node *p = head;
	while(p){
		printf("%d , ", p->data);
		p = p->next;
	}
}


int main(){
	int i;
	struct node ns[] = {
		{80, NULL},
		{8, NULL},
		{1, NULL},
		{10, NULL},
	};
	for(i = 0; i < 4; i++){
		insert2(&ns[i]);
	}
	show();

	return 0;
}





