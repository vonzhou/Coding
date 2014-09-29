#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	execve("/bin/ls", argv, envp);
	printf("vonzhou\n");
	return 0;
}
