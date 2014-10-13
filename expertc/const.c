#include <stdio.h>

int main(){
    int a = 100;
    int b = 10;
    int c = 4;
    int d = 1000;
    const int * grape = &a;
    int const * grape2 = &b;

    int * const grape_jelly = &c;

    const int * const grape_jam = &d;
    printf("a = %d, b = %d\n",a, b);
    //some actions
    a = 10;

    //*grape = 10;// error: assignment of read-only location ‘*grape’
    //可以直接修改a 但是不能通过指针来修改 相当于访问控制 ?\
    //对于b同样如此
    b = 100;
    // *grape2 = 0; // cannot

    grape = grape2;
    grape2 = &a;
    printf("a = %d, b = %d\n",a, b);

    c = 1000;
   // grape_jelly = grape;//error: assignment of read-only variable ‘grape_jelly’
    // *grape_jelly = 0;  // cannot   

    return 0;
}
