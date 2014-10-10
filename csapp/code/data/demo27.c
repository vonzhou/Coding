#include <stdio.h>

/*Determine wether arguments can be added without overflow*/
int uadd_ok(unsigned x, unsigned y){
    unsigned sum = x + y;
    return sum >= x;
}

int main(){
    unsigned x = 0xffffffff, y = 3;
    printf("uadd_ok : %d\n", uadd_ok(x, y));
    return 0;
}
