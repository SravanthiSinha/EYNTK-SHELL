#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - stdout to a file
 *
 * Return: EXIT_SUCCESS, or exit code
 */
int main(int argc, char **argv)
{
	FILE *fp;
	fpos_t position;

	if(argc != 2)
	{
		printf ("Usage: ./stdout_file <filename>\n");
		exit(1);
	}
	fp = fopen(argv[1], "w");
	if (dup2(fileno(fp), STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}

	/* Let's try to print something on stdout */
	printf("Test on stdout\n");
	printf("Holberton School\n");
	fclose(fp);
	return (EXIT_SUCCESS);
}
