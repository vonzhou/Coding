
#include <stdio.h>

/*习题 2.32*/


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

int tsub_ok(int x, int y){
    return tadd_ok(x, -y);
}

// can work
void test1(){
    int x = 0x80000000;
    int y = 0x7fffffff;
    printf("test1:%d\n", tsub_ok(x, y));
}

// cannot work , sub = TMax
// 当x负数，y = TMin的时候出现问题
void test2(){
    int x = -1;
    int y = 0x80000000; 
    printf("test2:%d\n", tsub_ok(x, y));
}

int main(){
    test1();
    test2(); ///
    int x = 0x80000000;
    printf("TMin = %.8x, -TMin = %.8x\n", x, -x);
    return 0;
}
/*
negative overflow....
test1:0
negative overflow....
test2:0
TMin = 80000000, -TMin = 80000000
 * */
