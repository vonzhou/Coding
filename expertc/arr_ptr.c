

#include <stdio.h>

int main(){
    int i = 0;
    char cs[] = "12345678";
    char (*j)[4] = cs;

    *(int *)(j+1) = 0;
    for(i=0; i<8; i++)
        printf("%d\t", cs[i]);

    printf("\n");
    return 0;
}
/*
vonzhou@de15:~/Coding/expertc$ gcc arr_ptr.c 
arr_ptr.c: In function ‘main’:
arr_ptr.c:8:20: warning: initialization from incompatible pointer type [enabled by default]
     char (*j)[4] = cs;
                         ^
vonzhou@de15:~/Coding/expertc$ ./a.out
49 50 51 52 0 0 0 0                               

*/


