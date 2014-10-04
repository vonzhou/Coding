/*
 * 程序清单 12-3 getenv 的非可重入版本
 *
 * 因为所有调用 getenv() 的线程返回的字符串都存放在一个静态缓冲区中，所以这个
 * 版本不是可重入的。如果两个线程同时调用这个函数，就会看到不一致的结果。
 */

#include <limits.h>
#include <string.h>

static char envbuf[ARG_MAX];

extern char **environ;

char *
getenv(const char *name)
{
  int i, len;

  len = strlen(name);
  for (i = 0; environ[i] != NULL; i++) {
    if ((strcmp(name, environ[i], len) == 0) &&
        (environ[i][len] == '=')) {
      strcpy(envbuf, &environ[i][len+1]);
      return envbuf;
    }
  }
  return NULL;
}

