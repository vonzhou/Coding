#include<stdio.h>
#include<string.h>

int main(void){
	char tmp[20];
	char *str = "vonzhou\n";
	memcpy((void *)tmp,str, strlen(str) + 1);// remember to include the tailing  '\0'
	printf("%s",tmp);
	
	return 0;
}


