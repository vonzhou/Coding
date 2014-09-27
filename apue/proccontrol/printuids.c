

// prag : 8-15
#include "util.h"

int
main(void)
{
	printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());
	exit(0);
}

