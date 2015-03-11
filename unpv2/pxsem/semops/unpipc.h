#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>   //va_arg ...
#include <mqueue.h>  // posix msg queue
#include <semaphore.h>

#define MAXLINE 80
#define HAVE_SEMAPHORE_H
// default file mode
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

















