#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: signal_sender <pid>\n");
        exit(0);
    }
    pid_t pid = (pid_t)atoi(argv[1]);
    kill(pid, SIGUSR1);

    return 0;
}
