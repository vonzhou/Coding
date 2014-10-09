
#include <stdio.h>

float sum_elements(float a[], unsigned length){
    int i;
    float res = 0;
    for(i = 0; i <= length -1; i++)
        res += a[i];
    return res;
}

float sum_elements2(float a[], unsigned length){
    int i;
    float res = 0;
    // or make length to int type
    for(i = 0; i < length ; i++)
        res += a[i];
    return res;
}

int main(){
    float a[] = {3,14, 5678, 1,3,7};
    //float res1 = sum_elements(a, 0);/* coredump !!*/
    float res1 = sum_elements2(a, 0);
    printf("result is %f\n", res1);

    return 0;
}

















