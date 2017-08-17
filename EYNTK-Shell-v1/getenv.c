#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name)
{
	int i = 0, j = 0;
	if (name)
	{
		while(environ[i])
		{
			while(environ[i][j++] != '=');
			if(strcmp(strndup(environ[i], j - 1), name) == 0)
			{
				return (environ[i] + j);
			}
			i++;
			j = 0;
		}
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	char *env;

	if(argc !=2)
	{
		printf("Usage: ./getenv <env>\n");
		exit(1);
	}
	env = _getenv(argv[1]);
	if(env)
		printf("%s -> %s\n", argv[1], env);
	return (0);
}
