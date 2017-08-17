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
	
	if(argc != 2)
	{
		printf ("Usage: ./stdout_end_file <filename>\n");
		exit(1);
	}
	fp = fopen(argv[1], "r+");
	if (dup2(fileno(fp), STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (EXIT_FAILURE);
	}

	if( access(argv[1], F_OK ) != -1 ) {
			if (lseek(fileno(fp),0,SEEK_END) == -1)
				exit(1);
		}
	/* Let's try to print something on stdout */
	printf("Test on stdout\n");
	printf("Holberton School\n");
	fclose(fp);
	return (EXIT_SUCCESS);
}
