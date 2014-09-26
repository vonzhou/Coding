#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** tokenize(const char* input, int *countp)
{
    char *str = strdup(input);// 复制一份进行操作
    int count = 0;
    int capacity = 10; //初始容量是10个单词,满后倍增
    char	**result = malloc(capacity*sizeof(*result));
	//printf("%d\n", sizeof(*result));
    char *tok=strtok(str," "); 

    while(1)
    {
        if (count >= capacity)
            result = realloc(result, (capacity *= 2) * sizeof(*result));

        result[count++] = tok ? strdup(tok) : tok; // 数组最后一项为NULL

        if (!tok) break;

        tok=strtok(NULL," ");
    } 
	*countp = count - 1;
    free(str);
    return result;
}

