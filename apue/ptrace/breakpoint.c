#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>    // ORIG_EAX
#include <sys/syscall.h>  // SYS_write
#include <sys/user.h>  // struct user_regs_struct ,

const int long_size = sizeof(long);

void getdata(pid_t pid, long addr, char *str, int len){
    char *laddr;
    int i, j;
    union u{
        long val;
        char chars[sizeof(long)];
    }data;
    i=0;
    j = len/sizeof(long);
    laddr = str;
    // every time got a 4B data from the traced process
    while(i < j){
        data.val = ptrace(PTRACE_PEEKDATA, pid, addr + i*4, NULL);
        memcpy(laddr, data.chars, sizeof(long));
        i++;
        laddr += long_size;
    }
    j = len % long_size;
    if(j != 0){
        data.val = ptrace(PTRACE_PEEKDATA, pid, addr + i*4, NULL);
        memcpy(laddr, data.chars, j);
    }
    str[len] = '\0';
}

void putdata(pid_t pid, long addr, char *str, int len){
    char *laddr;
    int i,j;
    union u{
        long val;
        char chars[long_size];
    }data;
    i=0;
    j=len/long_size;
    laddr = str;
    while(i<j){
        memcpy(data.chars, laddr, long_size);
        ptrace(PTRACE_POKEDATA, pid, addr+i*4, data.val);
        i++;
        laddr += long_size;
    }
    j = len % long_size;
    if(j != 0){
        memcpy(data.chars, laddr, j);
        ptrace(PTRACE_POKEDATA, pid, addr+i*4,data.val);
    }
}

int main(int argc, char **argv){
    int status;
    pid_t pid;
    long orig_eax, eax;
    struct user_regs_struct regs;
    char *str;
    long ins;
    // int 0x80, int3
    char code[] = {0xcd, 0x80, 0xcc, 0};
    char backup[4];
    if(argc != 2){
        printf("Usage : %s <pid>\n", argv[0]);
        exit(-1);
    }

    pid = atoi(argv[1]);
    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    wait(&status);
    
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    // back up the cuurent instruction
    getdata(pid, regs.eip, backup, 3);
    // put the breakpoint
    putdata(pid, regs.eip, code, 3);
    // let the process continue and execute the int3 instruction
    ptrace(PTRACE_CONT, pid, NULL, NULL);
    wait(&status);
    printf("The process stopped, putting back the original ins\n");
    printf("Press <enter> to continue\n");
    getchar();
    putdata(pid, regs.eip, backup, 3);
    // set EIP back to the stopped instruction
    ptrace(PTRACE_SETREGS, pid, NULL, &regs);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    printf("Tracer Exit...\n");
    return 0;
}





