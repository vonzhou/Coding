#include <stdio.h>

struct fd_set{
	int data[5];
};

int main(){
	struct fd_set fd1;
	fd1.data[2] = 5;
	struct fd_set fd2 = fd1;

	printf("%d\n", fd2.data[2]);
	return 0;

}