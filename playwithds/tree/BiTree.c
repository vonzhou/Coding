#include<stdio.h>
#include<stdlib.h>

typedef char TElemType;

typedef struct BiTNode{
	TElemType data;
	struct BiTNode * lchild, *rchild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree *T){
	TElemType ch;
	scanf("%c", &ch);
	if(ch == '#')
		*T = NULL;
	else{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if((*T) == NULL)
			exit(-1);
		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}

}


//先序遍历
void PreOrderTraverse(BiTree T){
	if(T == NULL)
		return;
	printf("%c\n", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}


int main(){
	
	BiTree T = NULL;
	CreateBiTree(&T);
	PreOrderTraverse(T);


}









