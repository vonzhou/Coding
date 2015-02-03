#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>    // ORIG_EAX
#include <sys/syscall.h>  // SYS_write
#include <sys/user.h>  // struct user_regs_struct ,
const int long_size = sizeof(long);

int main(){
    int status, start=0;
    pid_t pid;
    long orig_eax, eax;
    struct user_regs_struct regs;
    union u{
        long val;
        char chars[long_size];
    }data;
    long ins;

    switch(pid = fork()){
        case -1:
            perror("fork");
            break;
        case 0:
            // child process starts here
            ptrace(PTRACE_TRACEME, 0, 0, 0);
            execl("./dummy", "dummy", NULL);\
            break;
        default:
            // parent process

            while(1){
                wait(&status);
                if(WIFEXITED(status))
                    break;
               // orig_eax = ptrace(PTRACE_PEEKUSER, pid, 4 * ORIG_EAX, NULL);
                ptrace(PTRACE_GETREGS, pid, NULL, &regs);
                if(start==1){
                    ins = ptrace(PTRACE_PEEKTEXT, pid, regs.eip, NULL);
                    printf("EIP:%lx, Instruction executed:%lx\n", regs.eip, ins);
                }
                if(regs.orig_eax == SYS_write){
                    start = 1;
                    ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL);
                }else
                    ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
            } // end while
    }
    return 0;
}





