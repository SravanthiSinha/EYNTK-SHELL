#include <stdio.h>
#include <unistd.h>

/**
 * main - arguments
 *
 * Return: Always 0.
 */
int main(int argc, char** argv)
{
	int i = 0;

	while(argv[i])
	{
		printf("%s\n", argv[i++]);
	}

	return (0);
}
