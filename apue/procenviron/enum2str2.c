#include<stdio.h>
#include<stdlib.h>


/*将相应的枚举类型转为字符串(这种方法很重要)*/
#define FOREACH_CMD(CMD) \
        CMD(CMD_UNSPEC)   \
        CMD(CMD_ADD)  \
        CMD(CMD_SUB)   \
        CMD(CMD_MULTI)  \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum CMD_ENUM {
    FOREACH_CMD(GENERATE_ENUM)
};

static const char *CMD_STRING[] = {
    FOREACH_CMD(GENERATE_STRING)
};

int main(void){
	printf("%s\n", CMD_STRING[CMD_ADD]);
	exit(0);
}
