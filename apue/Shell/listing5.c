#include "util.h"

void fill_argv(char *tmp_argv)
{
	char *foo = tmp_argv;
	int index = 0;
	char ret[100];
	bzero(ret, 100);
	while(*foo != '\0') {
		if(index == 10)
			break;

		if(*foo == ' ') {
			if(my_argv[index] == NULL)
				my_argv[index] = (char *)malloc(sizeof(char) * strlen(ret) + 1);
			else {
				bzero(my_argv[index], strlen(my_argv[index]));
			}
			strncpy(my_argv[index], ret, strlen(ret));
			strncat(my_argv[index], "\0", 1);
			bzero(ret, 100);
			index++;
		} else {
			strncat(ret, foo, 1);
		}
		foo++;
	}
	if(ret[0] != '\0') { 
		my_argv[index] = (char *)malloc(sizeof(char) * strlen(ret) + 1);
		strncpy(my_argv[index], ret, strlen(ret));
		strncat(my_argv[index], "\0", 1);
	}
}

