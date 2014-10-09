
/*习题 2.13 */

#include <stdio.h>
#include <stdlib.h>

/*set the m th bit of x , just use built-in ops to emulation it */
int bis(int x, int m){
    /*just treating*/
    return x | m ;  
}

/*clear m th bit of x*/
int  bic(int x, int m){ 
    return x & (~m);
}

int bool_or(int x, int y){
    return bis(x, y);
}

int bool_xor(int x, int y){
    printf("%.4x -- %.4x\n", x, y);
    int a = bic(x, y);
    int b = bic(y, x);
    printf("%.4x -- %.4x\n", a, b);
    return bis(a, b);
}

void test_xor(){
    int x = 15;
    int y = 0x5;
    printf("after bool_xor(%.4x,%.4x) is %.4x\n", x, y, bool_xor(x, y));
}


void test_bis(){
    int x = 8;
    int y = bis(x, 1);
    printf("after bis %x => %x\n", x, y);
}

 void test_bic(){
     int x = 5;
     int y = 15;
     int res = bic(x, y);
     printf("after bic(%x, %x) is %x\n", x, y, res);
 }

int main(){
    //test_bis();
    test_bic();
    test_xor();
    return 0;
}











