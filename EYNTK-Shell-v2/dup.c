#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - dup2
 *
 * Return: EXIT_SUCCESS, or exit code
 */
int main(void)
{
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}

	/* Let's try to print something on stdout */
	printf("Test on stdout\n");
	printf("Holberton School\n");
	return (EXIT_SUCCESS);
}
