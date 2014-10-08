/*
 * 程序清单 12-4 getenv 的可重入（线程安全）版本
 *
 * getenv_r() 使用 pthread_once() 来确保每个进程只调用一次 thread_init()。
 */

#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

extern char **environ;

pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

/*
 * Using PTHREAD_MUTEX_RECURSIVE_NP under Ubuntu Linux 10.04.3 LTS,
 * with kernel 2.6.32-38-generic, instead of PTHREAD_MUTEX_RECURSIVE.
 */
static void
thread_init(void)
{
  pthread_mutexattr_t attr;

  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
  pthread_mutex_init(&env_mutex, &attr);
  pthread_mutexattr_destroy(&attr);
}

int
getenv_r(const char *name, char *buf, int buflen)
{
  int i, len, olen;

  pthread_once(&init_done, thread_init);
  len = strlen(name);
  pthread_mutex_lock(&env_mutex);
  for (i = 0; environ[i] != NULL; i++) {
    if ((strncmp(name, environ[i], len) == 0) &&
        (environ[i][len] == '=')) {
      olen = strlen(&environ[i][len+1]);
      if (olen >= buflen) {
        pthread_mutex_unlock(&env_mutex);
        return ENOSPC;
      }
      strcpy(buf, &environ[i][len+1]);
      pthread_mutex_unlock(&env_mutex);
      return 0;
    }
  }
  pthread_mutex_unlock(&env_mutex);
  return ENOENT;
}

