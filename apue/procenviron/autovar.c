
// - 7.10
// 没有看到出错的结果！！！
#include <stdio.h>
#include <stdlib.h>

int f(int val){
	int *ptr;
	if(val ==0){
		int val ;
		val = 5;
		ptr = &val;
	}
	return (*ptr + 1);
}

int f2(int x){
	x = x * x;
	printf("in f2 : %d\n", x);
	return x;
}


int main(){
	int val = f(0);
	int i = 10;
	for(i=0 ; i < 10; i++){
		int x = i *i;
	}
	f2(10);
	printf("%d\n", val);
}



















