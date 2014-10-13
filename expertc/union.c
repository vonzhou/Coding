
#include <stdio.h>

union bits32_tag{
    int whole;
    struct {
        char cs[4];
    }byte;
}value;

int main(){
    value.whole = 0x12345678;
    printf("whole : %x\n", value.whole);
    int i;
    for(i=0; i<4;i++){
        printf("byte[%d] : %x\n", i, value.byte.cs[i]);
    }
    
}

/*
 vonzhou@de15:~/Coding/expertc$ gcc union.c 
 vonzhou@de15:~/Coding/expertc$ ./a.out
whole : 12345678
byte[0] : 78
byte[1] : 56
byte[2] : 34
byte[3] : 12 可以用来判断大小端模式??
 * */
