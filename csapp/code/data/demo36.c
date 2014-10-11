
/* 习题 2.36*/

#include <stdio.h>
#include <stdlib.h>

/*using long long */
int tmult_ok(int x, int y){
    long long pll = (long long )x * y; // must cast
    return pll == (int)pll;
}


int main(){
    int ele_cnt = 1048577;
    int ele_size = 4096;
    printf("sizeof long long :%d\n", sizeof(long long));
    printf("sizeof long :%d\n", sizeof(long));
    printf("mult test : %d\n", tmult_ok(ele_cnt, ele_size));    
    exit(0);
}
/*
 sizeof long long :8
 sizeof long :8
 mult test : 0
 * */

