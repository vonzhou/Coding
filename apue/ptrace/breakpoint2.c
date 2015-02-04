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
    int len = 41; 
    char code[] = "\xeb\x15\x5e\xb8\x04\x00\x00\x00"
                  "\xbb\x02\x00\x00\x00\x89\xf1\xba"
                  "\xc0\x00\x00\x00\xcd\x80\xcc\xe8"
                  "\xe6\xff\xff\xff\x48\x65\x6c\x6c"
                  "\x6f\x20\x57\x6f\x72\x6c\x64\x0a\x00"
        ;

    char backup[len];
    if(argc != 2){
        printf("Usage : %s <pid>\n", argv[0]);
        exit(-1);
    }

    pid = atoi(argv[1]);
    ptrace(PTRACE_ATTACH, pid, NULL, NULL);
    wait(&status);
    
    ptrace(PTRACE_GETREGS, pid, NULL, &regs);
    // back up the cuurent instruction
    getdata(pid, regs.eip, backup, len);
    // put the breakpoint
    putdata(pid, regs.eip, code, len);
    // let the process continue and execute the int3 instruction
    ptrace(PTRACE_SETREGS, pid, NULL, &regs);
    ptrace(PTRACE_CONT, pid, NULL, NULL);
    wait(&status);
    printf("The process stopped, putting back the original ins\n");
    //printf("Press <enter> to continue\n");
    //getchar();
    putdata(pid, regs.eip, backup, len);
    // set EIP back to the stopped instruction
    ptrace(PTRACE_SETREGS, pid, NULL, &regs);
    ptrace(PTRACE_DETACH, pid, NULL, NULL);
    //printf("Tracer Exit...\n");
    return 0;
}





