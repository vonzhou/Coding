#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int our_init_data = 30;
int our_noinit_data;

void our_prints(void)
{
        int our_local_data = 1;
        printf("\nPid of the process is = %d", getpid());
        printf("\nAddresses which fall into:");
        printf("\n 1) Data  segment = %p",
                &our_init_data);
        printf("\n 2) BSS   segment = %p",
                &our_noinit_data);
        printf("\n 3) Code  segment = %p",
                &our_prints);
        printf("\n 4) Stack segment = %p\n",
                &our_local_data);

	while(1);  // 使得我们可以看到该进程的信息
}

int main()
{
        our_prints();
        return 0;
}
