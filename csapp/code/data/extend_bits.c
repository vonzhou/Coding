
#include "data.h"

/*P49*/
void test(){
    short sx = -12345;
    unsigned short usx = sx;
    int x = sx;
    unsigned ux = usx;

    printf("sx = %d:\t", sx);
    show_bytes((byte_pointer)&sx, sizeof(short));
    printf("usx = %u:\t", usx);
    show_bytes((byte_pointer)&usx, sizeof(unsigned short));
    printf("x = %d:\t", x);
    show_bytes((byte_pointer)&x, sizeof(int));
    printf("ux = %u:\t", ux);
    show_bytes((byte_pointer)&ux, sizeof(unsigned int));
}

int main(){
    test();
    return 0;
}


/*
vonzhou@de15:~/Coding/csapp/code/data$ gcc extend_bits.c 
vonzhou@de15:~/Coding/csapp/code/data$ ./a.out
sx = -12345:c7c f
usx = 53191:c7cf
x = -12345:c7cfffff
ux = 53191:c7cf0000         
*/



