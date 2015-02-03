#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>    // ORIG_EAX
#include <sys/syscall.h>  // SYS_write
#include <sys/user.h>  // struct user_regs_struct ,
int main(){
    int status, insyscall=0;
    pid_t pid;
    long orig_eax, eax;
    struct user_regs_struct regs;

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
                        // syscall entry
                        insyscall = 1;
                        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
                        printf("Write called with %ld,%ld,%ld\n", 
                                regs.ebx, regs.ecx, regs.edx);
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





