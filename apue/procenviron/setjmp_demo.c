/* 
 * 	Illustrates setjmp and longjmp:
 *
 * 		int setjmp(jmp_buf env);
 * 		void longjmp(jmp_buf env, int val);
 *
 * 	In this demo, the use types any string at a prompt
 *
 * 	(1) if the string begins with a '1', it will "restart"
 * 	(2) if the string begins with a '2', it will exit.
 * 	(3) otherwise, the string is echoed back
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf env;

nested_print(char *buf)
{
	if (buf[0] == '1') longjmp(env,1);
	if (buf[0] == '2') longjmp(env,2);
	printf("%s\n", buf);
}

print(char *buf)
{
	nested_print(buf);
}

main() {
	int r, k = 0, j = 0;
	char buf[BUFSIZ];

	// initialize:
	printf("setjmp demo\n");

	// restart location
	if ((r=setjmp(env)) != 0){// code for longjump return!
		if (r==2)
			exit(0);
		// else, r must be 1:
		printf("restarted... after %d\n", j);
		j = 0;
	}

	// loop
	for (;;) {
		printf("%d> ", ++k);
		j++;
		gets(buf);
		print(buf);
	}
}//main





















