#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
	pid_t child_pid;
	int status;
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};
	int i = 0;

	while(i++ < 5)
	{
		child_pid = fork();
		if(child_pid == 0)
		{
			execve(argv[0], argv, NULL);
		}
		if (child_pid != 0)
		{
			wait(&status);
			printf("%u %u\n", getpid(), child_pid);
		}
	}
	return(0);
}
