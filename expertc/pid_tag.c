
#include <stdio.h>

struct pid_tag{
    unsigned int inactive : 1;
    unsigned int : 1 ; // 1 bit padding
    unsigned int refcount : 6;
    unsigned int :0;  // padding to next word bound
    short pid_id;
    //....
};

int main(){
    struct pid_tag t;
    t.refcount = 10;
    t.inactive = 0;
    printf("%x\n", &t);
    //注意 cannot take address of bit-field ‘refcount’
    printf("%x\n",&(t.pid_id));
    return 0;
}
