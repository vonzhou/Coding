
/*习题 2.11*/

#include <stdio.h>

void inplace_swap(int *x, int *y){
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

void reverse_array(int a[], int cnt){
    int first = 0, last = cnt - 1;
    for(; first < last; first++, last --)
        inplace_swap(&a[first], &a[last]);
}

void show_array(int a[], int cnt){
    int i=0;
    for(; i < cnt; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void test_odd(){
    int a[] = {1, 3, 5, 7, 9};
    reverse_array(a, 5);
    show_array(a, 5);
}

 void test_even(){
     int a[] = {1, 3, 5, 7, 9, 11}; 
     reverse_array(a, 6); 
     show_array(a, 6); 
 }

int main(){
    test_odd();
    test_even();
    return 0;
}













