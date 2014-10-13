
#include <stdio.h>

struct s_tag{int a[100];};

struct s_tag twofold(struct s_tag s){
    int j = 0;
    for(j=0;j<100;j++)
        s.a[j] *= 2;
    return s;
}

int main(){
    int i;
    struct s_tag orange, lime, lemon;
    for(i = 0; i<100; i++)
        lime.a[i] = i;
    lemon = twofold(lime);
    orange = lemon;

    for(i=0; i<100; i++)
        printf("%d ", lemon.a[i]);
    return 0;
}
