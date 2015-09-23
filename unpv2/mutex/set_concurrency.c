#include	"../unpipc.h"

int
set_concurrency(int level)
{
	// vonzhou
	// on Linux we have pthread_setconcurrency
	pthread_setconcurrency(level);
}

void
Set_concurrency(int level)
{
	if (set_concurrency(level) != 0)
		err_sys("set_concurrency error");
}
