
#include <stdio.h>

int main(){
    char *s = "abcaaaaaaaaaa";
    printf("%s\n", s);
    return 0;
}

/*
 vonzhou@de15:~/Coding/expertc$ gcc string_literal.c 
 vonzhou@de15:~/Coding/expertc$ size a.out
 text   data         bss    dec    hex filename
 1148    552            8   1708    6ac   a.out
 vonzhou@de15:~/Coding/expertc$ vi string_literal.c
 vonzhou@de1  5:~/Coding/expertc$ gcc string_literal.c 
 vonzhou@de15:~/Coding/expertc$ size a.out
 text   data    bss    dec    hex filename
 1158    552      8   1718    6b6  a.out    
 * 当字符串常量增大10个时候，可以看到文本段也对应增大了
 * **/
