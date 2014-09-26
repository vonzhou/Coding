#include "util.h"

void	do_line(char *);
void	cmd_add(void);


#define FOREACH_CMD(CMD) \
        CMD(CMD_UNSPEC)   \
        CMD(CMD_ADD)  \
        CMD(CMD_SUB)   \
        CMD(CMD_MULTI)  \
		CMD(CMD_LIMIT) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum CMD_ENUM {
    FOREACH_CMD(GENERATE_ENUM)
};

static const char *CMD_STRING[] = {
    FOREACH_CMD(GENERATE_STRING)
};

int main(void){
	char	line[MAXLINE];
	//printf("%s\n", CMD_STRING[CMD_ADD]);

	if (fgets(line, MAXLINE, stdin) != NULL)
		do_line(line);

	exit(0);
}

void do_line(char *ptr)		/* process one line of input */
{
	int		cmd, i;
	int count , result = 0;
	char **words = tokenize(ptr, &count);
	if(count < 2){
		//至少有一个加数，这里假设输入时合法的
	}
	
	// 假设只是两个数加法
	// C 语言不能用字符串做索引，所以需要找到字符串命令对应的枚举值
	for(i = 0; i < CMD_LIMIT; i++)
		if(strcmp(words[0], CMD_STRING[i]) == 0)
			break;

	switch(i){
		case CMD_ADD:
			// cmd_add 应该单独分离出一个函数
			for(i = 1; i < count ; i++){
        		result += atoi(words[i]);
    		}
			printf("ADD Result is %d\n", result);
			break;
		default:
			// 这里需要释放内存
			printf("Invalid\n");
			break;	  
	}
	//printf("CMD is  %d\n", i);
	//printf("words count : %d\n", count);
	//最后统一释放内存
	for(i = 0; i < count ; i++)
		free(words[i]);
	free(words);  //
}



