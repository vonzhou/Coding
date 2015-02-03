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

void reverse(char *str){
    int i, j, mid;
    char temp;
    j = strlen(str)-1;
    mid = j/2 - 1;
    for(i=0; i<=mid; i++){
        temp = str[i];
        str[i] = str[j-1-i];
        str[j-1-i] = temp;
    }
}

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

int main(){
    int status, insyscall=0;
    pid_t pid;
    long orig_eax, eax;
    struct user_regs_struct regs;
    char *str;

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
                        printf("Write called with %ld,%p,%ld\n", 
                                regs.ebx, (char *)regs.ecx, regs.edx);
                        str = (char *)malloc((regs.edx+1)* sizeof(char));
                        getdata(pid, regs.ecx, str, regs.edx);
                        reverse(str);
                        putdata(pid, regs.ecx, str, regs.edx);
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





