#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>   // open()

#include <errno.h>
#include <string.h>  // strerror()


int main(){
    int fd;
    setuid(0); // become the superuser to open the master file
    fd = open("/etc/shadow", O_RDONLY);
    setuid(-1); // give up the privelige
    if(fd < 0){
        printf("open error! %s(errno=%d)\n", strerror(errno), errno);
        exit(-1);
    }

    // do something with fd


    return 0;
}
