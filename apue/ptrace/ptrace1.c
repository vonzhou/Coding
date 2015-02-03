#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>    // ORIG_EAX
int main(){
    int val;
    pid_t pid;
    long orig_eax;
    switch(pid = fork()){
        case -1:
            perror("fork");
            break;
        case 0:
            // child process starts here
            ptrace(PTRACE_TRACEME, 0, 0, 0);
            execl("/bin/ls", "ls", NULL);\
            break;
        default:
            // parent process
            wait(&val);
            orig_eax = ptrace(PTRACE_PEEKUSER, pid, 4 * ORIG_EAX, NULL);
            printf("The child made a syscall %ld\n", orig_eax);
            ptrace(PTRACE_CONT, pid, NULL, NULL);
    }
    return 0;
}





