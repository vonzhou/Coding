
#include <stdio.h>
#include <string.h>

int strlonger(char *s, char *t){
    return strlen(s)-strlen(t) > 0;
}

int strlonger2(char *s, char *t){
    return strlen(s) > strlen(t); // 直接关系运算
}

void test1(){
    char *s = "abcd";
    char *t = "a";
    printf("test1 : %d\n", strlonger(s, t));
    printf("test1 : %d\n", strlonger2(s, t));
}

void test2(){
    char *s = "abcd";
    char *t = "vonzhou";
    printf("test2 : %d\n", strlonger(s, t));
    printf("test2 : %d\n", strlonger2(s, t));
}

void test3(){
    char *s = "";
    char *t = "";
    printf("test1 : %d\n", strlonger(s, t));
    printf("test2 : %d\n", strlonger2(s, t));
}

int main(){
    test1();
    test2();
    test3();
    return 0;
}
