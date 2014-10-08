
/*习题 2.10*/

#include <stdio.h>

void inplace_swap(int *x, int *y){
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

int main(){
    int x = 100;
    int y = 9999;
    printf("x= %d, y = %d\n", x, y);
    inplace_swap(&x, &y);
    printf("x= %d, y = %d\n", x, y);
}













