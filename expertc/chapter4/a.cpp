#include <iostream>

using namespace std;

int main(){

	const int a =10;
	int *p = (int *) (&a);
	*p =20;

	cout << a<< endl << *p <<endl;
}
