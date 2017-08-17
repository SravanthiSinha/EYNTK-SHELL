#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(void)
{
	int i = 0;

	while(environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
