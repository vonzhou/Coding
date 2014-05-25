#include<stdio.h>
int main(){
	int i = 0;
	int j=(i++)+(++i)+(++i);
	int x = 0;
        int y=(x++)+(++x);
//	printf("%d\n",(i++)+(++i)+(++i));
	printf("%d,%d\n",i,j);
	printf("%d,%d\n",x,y);

}
