#include	<stdio.h>

#define	DATAFILE	"datafile"

FILE *
open_data(void)
{
	FILE	*fp;
	char	databuf[BUFSIZ];  /* setvbuf makes this the stdio buffer */

	if ((fp = fopen(DATAFILE, "r")) == NULL)
		return(NULL);
	if (setvbuf(fp, databuf, _IOLBF, BUFSIZ) != 0)
		return(NULL);
	return(fp);		/* error */
}

void func(int x){
	int a = 9;
	printf("%d\n", x + 9);
}

int main(){

	FILE *file = open_data();
	printf("==============\n");
	func(10);
	return 0;
}
