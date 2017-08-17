#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_END    0
#define WRITE_END   1

/**
 * main - pipe(2) manual page example
 * @argc: Arguments counter
 * @argv: Arguments vector
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if (cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0)                 /* Child reads from pipe */
	{
		close(pipefd[WRITE_END]);          /* Close unused write end */
		while (read(pipefd[READ_END], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);
		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[READ_END]);
		_exit(EXIT_SUCCESS);
	}
	else                           /* Parent writes argv[1] to pipe */
	{
		close(pipefd[READ_END]);          /* Close unused read end */
		write(pipefd[WRITE_END], argv[1], strlen(argv[1]));
		close(pipefd[WRITE_END]);          /* Reader will see EOF */
		wait(NULL);                /* Wait for child */
		exit(EXIT_SUCCESS);
	}
}
