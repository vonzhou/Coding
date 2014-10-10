
#include <stdio.h>

/*Whether arguments can be added without overflow*/
int tadd_ok(int x, int y){
    int sum = x + y;
    int neg_overflow = x < 0 && y < 0 && sum >= 0;
    int pos_overflow = x >= 0 && y>= 0 && sum < 0;
    if(neg_overflow)
        printf("negative overflow....\n");
    if(pos_overflow)
        printf("positive overflow...\n");
    return !neg_overflow && !pos_overflow;
}

int main(){
    int x = 0x80000000;
    int y = 0x87654321;
    printf("%d\n", tadd_ok(x, y));
    return 0;
}

