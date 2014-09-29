void call_execve(char *cmd)
{
	int i;
	if(fork() == 0) {
		i = execlp(cmd, my_argv, my_envp);
		if(i < 0) {
			printf("%s: %s\n", cmd, "command not found");
			exit(1);		
		}
	} else {
		wait(NULL);
	}
}
