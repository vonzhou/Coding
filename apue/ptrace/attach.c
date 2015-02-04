#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>    // ORIG_EAX
#include <sys/syscall.h>  // SYS_write
#include <sys/user.h>  // struct user_regs_struct ,
#include <errno.h>


int main(int argc, char **argv){
    int status;
    pid_t traced_pid;
    long orig_eax, eax;
    struct user_regs_struct regs;
    long ins;

    if(argc != 2){
        printf("Usage : %s <pid to be traced>\n", argv[0]);
        exit(-1);
    }

    traced_pid = atoi(argv[1]);
    ptrace(PTRACE_ATTACH, traced_pid, NULL, NULL);
    wait(&status);
    if(WIFSTOPPED(status))
        printf("The tracee stopped, signal is SIGSTOP?:%d\n", (WSTOPSIG(status)==SIGSTOP));
    ptrace(PTRACE_GETREGS, traced_pid, NULL, &regs);
    printf("Orig_eax :%ld, eax: %ld\n", regs.orig_eax, regs.eax);
    printf("The eax(return value) is ERESTART ?: %d\n", 
            (regs.eax== ERESTART));
    ins = ptrace(PTRACE_PEEKDATA, traced_pid, regs.eip, NULL);
    printf("EIP:%lx, Instruction executed: %lx\n", regs.eip, ins);
    ptrace(PTRACE_DETACH, traced_pid, NULL, NULL);
    
    return 0;
}





