
#include <stdio.h>
#include <stdlib.h>

int fun1(unsigned word){
    return (int)((word << 24) >> 24);
}

int fun2(unsigned word){
    return (((int)word << 24) >> 24);
}

int main(){
    unsigned x = 0x87654321;
    printf("%x\n", fun1(x));
    printf("%x\n", fun2(x));
    
    x = 0xedcba987;
    printf("%x\n", fun1(x));
    printf("%x\n", fun2(x));
    return 0;
}
