
#include <stdio.h>

/*Not work !!!*/
int tadd_ok(int x, int y){
    int sum = x + y;
    return (sum-x == y) && (sum-y == x);
}

int main(){
    int x = 0x80000000;
    int y = 0x87654321;
    printf("overflow but return %d\n", tadd_ok(x, y));
    return 0;
}

