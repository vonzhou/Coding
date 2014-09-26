#include<stdio.h>
#include<stdlib.h>


enum cmd{
	CMD_UNSPEC = 0,
	CMD_ADD,
	CMD_SUB,
	CMD_MULTI,
	CMD_DIV,
};
static inline char * cmd_str(enum cmd c){
	static const char *strings[] = {"CMD_UNSPEC", "CMD_ADD", "CMD_SUB", "CMD_MULTI", "CMD_DIV", };
	return strings[c];
}

int main(void){
	
	printf("%s\n", cmd_str(CMD_ADD));

	exit(0);
}
