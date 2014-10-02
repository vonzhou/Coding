
#include "util.h"

static void sig_int(int signo){
    printf("Caught SIGINT \n");
}
static void sig_chld(int signo){
    printf("Caught SIGCHLD \n");
}
int main(){
 if(signal(SIGINT, sig_int)  == SIG_ERR)
     err_sys("signal(SIGINT) error");
 if(signal(SIGCHLD, sig_chld) == SIG_ERR)
     err_sys("signal(SIGCHLD) error");

 if(system("/bin/ed") < 0)
     err_sys("system(ed) error");

 exit(0);
}
