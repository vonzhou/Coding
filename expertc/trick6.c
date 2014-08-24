#include <stdio.h>

int main(){
	
	int n = 6;
	int val = 1000;
	char s[100];
	printf("%*d", n, val);// with a minimum width of n,default right aligned	
	printf("hello\n");

	//scanf("%*d");//read an integer and ignore it

	//scanf has regex built into it
	//read only selected chars into a string
	//scanf("%[abcd]s", s);

	
	//read everything excepted heading with abcd
	//scanf("%[^abcd]s" ,s);

	/* some complain that scanf reads upto a whitespace, 
	so this trick can be used to consume everything upto a newline */
	scanf("%[^\n]s", s); 
	// reads all chars (including whitespaces) till newline is encountered.

	printf("s = %s\n", s);
	/* Another trick with scanf is to consume what is required. 
	For example - If  a user enters his date of birth in YYYY-MM-DD 
	then you can directly read the year month and date into integer variables */
	//scanf("%d-%d-%d", &yy, &mm, &dd); 
	/* where yy, mm, dd are variables.
	Note that this will work only with that format of input. 
	Anything else like YYYY/MM/DD,and the program will mostly crash. 
	You specify a hyphen, it expects only a hyphen! */

	return 0;
}
