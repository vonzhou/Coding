
#include <stdio.h>

int mango[100];


void func(){
    printf("mango defined here\n");
    int i = 0;
    for(i=0; i<100;i++)
        mango[i] = 100-i;
}



