#include <stdio.h>

//extern int mango[];
extern int *mango;

void func2(){
    printf("mango declared and used  here\n");
    printf("mango[0] : %d\n", mango[0]);
}

int main(){
    func();
    func2();
    return 0;
}

/*
mango defined here
mango declared and used  here
Segmentation fault (core dumped)
*/
