//#include <iostream>
#include <stdio.h>
//using namespace std;

void func(int n){
	//int i;
	int arr[n];//  = {0};
	for(int i=0; i < n; i++)
		arr[i] = i;
	
	for( int i=0; i < n; i++)
		printf("%d  ",arr[i]);
}

int main(){
	int len = 7;
	//int arr[7][7][7];
	//int arr2[7];
	//arr[0][0][7] = 10;
	//arr2[7]  =9;
	//cout << arr[0][0][7] << endl;
	int n;
	int arr[n];
	//scanf("%d",&n);
	func(n);
	//cout << arr2[7] << endl;
	return 0;
}
