
// APUE p208

#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>   // getlogin()

int main()
{
    struct passwd *my_info;
	char *s = getlogin();
    my_info = getpwnam(s);
    //my_info = getpwnam( "fflg" );
    printf( "my name     = [%s]\n", my_info->pw_name     );
    printf( "my passwd = [%s]\n", my_info->pw_passwd );
    printf( "my uid          = [%d]\n", my_info->pw_uid          );
    printf( "my gid          = [%d]\n", my_info->pw_gid          );
    printf( "my gecos    = [%s]\n", my_info->pw_gecos     );
    printf( "my dir           = [%s]\n", my_info->pw_dir           );
    printf( "my shell       = [%s]\n", my_info->pw_shell       );
} 

