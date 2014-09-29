
// 为何不直接读取一整行呢?

int main(int argc, char *argv[], char *envp[])
{
	/* do some initializations. */
	while(c != EOF) {
		c = getchar();
		switch(c) {
			case '\n': /* parse and execute. */
				   bzero(tmp, sizeof(tmp));
				   break;
			default: strncat(tmp, &c, 1);
				 break;
		}
	}
	/* some processing before terminating. */
	return 0;
}
