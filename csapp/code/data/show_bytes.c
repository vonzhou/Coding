
#include "data.h"

void show_bytes(byte_pointer start, int len){
    int i =0;
    for(i = 0; i < len ;i++)
        printf("%.2x", start[i]);
    printf("\n");
}

void show_int(int x){
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float f){
    show_bytes((byte_pointer)&f, sizeof(f));
}

void show_pointer(void *x){
    show_bytes((byte_pointer)&x, sizeof(void *));
}




