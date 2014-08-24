#include<stdio.h>
#define MAX 100

int  main(){
	int i = 0;
	char s1[MAX],s2[MAX];

	//scanf("%[^\n]\n",s1);
	//read till meet '\n',and then trash the \n
	
	//scanf("%[^,]",s1); //?? also will  trash the coma
	//scanf("%[^,],",s1); // this does not trash the coma
	
	//this * can make us skip some input
	//for example,we just care the last-name
	scanf("%*s %s",s1);

	printf("%s\n",s1);



	return 0;
}

