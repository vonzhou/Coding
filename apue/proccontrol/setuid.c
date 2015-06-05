#include <stdio.h>
#include <unistd.h>

int main(){
    setuid(0); // SETUID to root
    system("./perm.sh");
    return 0;
}
