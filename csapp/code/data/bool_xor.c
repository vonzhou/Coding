
/*习题 2.13 */

#include <stdio.h>
#include <stdlib.h>

/*set the m th bit of x , just use built-in ops to emulation it */
int bis(int x, int m){
    if(m>32 || m < 1)
        exit(-1);
    return x | 1 << (m-1);  
}

/*clear m th bit of x*/
int  bic(int x, int m){
    if(m>32 || m < 1)
        exit(-1);
    return x & ~(1<<(m-1));
}

int bool_or(int x, int y){
    return bis(x, y);
}




void test_bis(){
    int x = 8;
    int y = bis(x, 1);
    printf("after bis %x => %x\n", x, y);
}

 void test_bic(){
     int x = 15;
     int y = bic(x, 4);
     printf("after bis %x => %x\n", x, y);
 }

int main(){
    //test_bis();
    test_bic();
    return 0;
}











