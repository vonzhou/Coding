#include <stdio.h>


int main(){

	int i=0;
	int j;
	for(j=0; j<5; j++){
		i = i++;
		printf("%d\n", i);
	}
	return 0;
}
