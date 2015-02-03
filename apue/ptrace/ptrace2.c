#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>    // ORIG_EAX
#include <sys/syscall.h>  // SYS_write

int main(){
    int status, insyscall=0;
    pid_t pid;
    long orig_eax, eax;
    long params[3];

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
            while(1){
                wait(&status);
                if(WIFEXITED(status))
                    break;
                orig_eax = ptrace(PTRACE_PEEKUSER, pid, 4 * ORIG_EAX, NULL);
                if(orig_eax == SYS_write){
                    if(insyscall == 0){
                        insyscall = 1;
                        params[0] = ptrace(PTRACE_PEEKUSER, pid, 4*EBX, NULL);
                        params[1] = ptrace(PTRACE_PEEKUSER, pid, 4*ECX, NULL);
                        params[2] = ptrace(PTRACE_PEEKUSER, pid, 4*EDX, NULL);
                        printf("Write called with %ld,%ld,%ld\n", 
                                params[0], params[1],params[2]);
                    }else{
                        // exit syscall 
                        eax = ptrace(PTRACE_PEEKUSER, pid, 4*EAX, NULL);
                        printf("Write returned with %ld\n", eax);
                        insyscall = 0;
                    }
                }
                ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
            }
    }
    return 0;
}





