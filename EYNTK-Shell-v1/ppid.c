#include <stdio.h>
#include <unistd.h>

/**
 * main - Parent PID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t parent_pid;

	parent_pid = getppid();
	printf("%u\n", parent_pid);
	return (0);
}
