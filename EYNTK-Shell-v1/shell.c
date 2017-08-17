#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	pid_t child_pid;
	int status;
	size_t len = 0;
	ssize_t read = 0;
	char *line = NULL;
	char *argv[2];

	printf("cisfun$");
	while ((read = getline(&line, &len, stdin)) > 0)
	{
		if (strchr(line, '\n'))
		{
			child_pid = fork();
			argv[0] = strtok(line, "\n");
			argv[1] = NULL;
			if (child_pid == 0)
			{
				if (execve(argv[0], argv, NULL) == -1)
				{
					perror("Error:");
				}
			}
			if (child_pid != 0)
			{
				wait(&status);
				printf("cisfun$");
			}
		}
	}
		return (0);
}
