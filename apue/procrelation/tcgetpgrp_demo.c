#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

main()
{
   pid_t stdin_PGID, stdout_PGID, stderr_PGID;

      /* Get the PGIDs for stdin, stdout, and stderr.  */
   stdin_PGID = tcgetpgrp(STDIN_FILENO);
   if (stdin_PGID == -1) {
      printf("Could not get PGID for stdin.\n");
      return(EXIT_FAILURE);
   }
   stdout_PGID = tcgetpgrp(STDOUT_FILENO);
   if (stdout_PGID == -1) {
      printf("Could not get PGID for stdout.\n");
      return(EXIT_FAILURE);
   }
   stderr_PGID = tcgetpgrp(STDERR_FILENO);
   if (stderr_PGID == -1) {
      printf("Could not get PGID for stderr.\n");
      return(EXIT_FAILURE);
   }
	printf("The current PID is %d. \n", getpid());
   printf("The PGID for stdin is %d.\n", stdin_PGID);
   printf("The PGID for stdout is %d.\n", stdout_PGID);
   printf("The PGID for stderr is %d.\n", stderr_PGID);

   return(EXIT_SUCCESS);
}


