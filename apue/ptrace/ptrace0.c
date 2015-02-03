#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

int main(){
    long long counter = 0;
    int val;
    int pid;
    switch(pid = fork()){
        case -1:
            perror("fork");
            break;
        case 0:
            // child process starts here
            ptrace(PTRACE_TRACEME, 0, 0, 0);
            execl("./hello", "hello", NULL);\
            break;
        default:
            // parent process
            wait(&val);
            while(WIFSTOPPED(val)){
                if(WSTOPSIG(val) == SIGTRAP){
                    counter ++;
                    if(ptrace(PTRACE_SINGLESTEP, pid, 0, 0))
                        perror("prace.");
                    wait(&val);
                }
            }
    }
    // last time is to exit
    if(WIFEXITED(val))
        printf("Normal termination, exit status=%d\n", WEXITSTATUS(val));
    printf("Machine Instructions count: %lld\n", counter);
    return 0;
}





