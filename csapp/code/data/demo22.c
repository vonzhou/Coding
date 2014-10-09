
#include "data.h"

int main(){
    short sx = -12345;
    unsigned uy = sx; /*NB*/

    printf("uy = %u:\t", uy);
    show_bytes((byte_pointer)&uy, sizeof(unsigned));

    printf("------------\n");

    int z = sx;
    printf("z = %d:\t", z);
    show_bytes((byte_pointer)&z, sizeof(int));
    
    return 0;
}

/*
vonzhou@de15:~/Coding/csapp/code/data$ gcc demo22.c show_bytes.o
vonzhou@de15:~/Coding/csapp/code/data$ ./a.out
uy = 4294954951:c7cfffff
------------
z = -12345:c7cfffff 
 * */
