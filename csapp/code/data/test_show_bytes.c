
#include "data.h"

void test_show_bytes(int val){
    int x = val;
    float f = (float)x;
    int *p = &x;
    show_int(x);
    show_float(f);
    show_pointer(p);
}
/* 习题2.5*/

void test25(){
    int val = 0x87654321;
    byte_pointer p = (byte_pointer)&val;
    show_bytes(p, 1);
    show_bytes(p, 2);
    show_bytes(p, 3);
}
/*习题 2.6*/
void test26(){
    int x = 3510593;
    //float y = 3510953.0; // 0xa44a564a
    float y = (float)x;   // 0x0445564a
    /*这两种表示得到的字节序列为何不一样??*/
    //printf("====%f\n",y);
    show_int(x);
    show_float(y);
    /*TODO 把hex转换成二进制字符串，然后模式匹配最长区间*/
}

/* 习题 2.7 */
void test27(){
    const char *s = "abcdef";
    show_bytes((byte_pointer)s, strlen(s));
}


int main(){
    test_show_bytes(100);
    test25();
    test26();
    test27();
    return 0;
}


/*
vonzhou@de15:~/Coding/csapp/code$ ./a.out
64000000     说明是小端模式
0000c842
e0713182ff7f0000
----------------
21
2143
214365
----------------
41913500
0445564a
---------------
616263646566 
*/



