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

void swap(char *a, char *b)
{
	char *c;

	c = b;
	b = a;
	a = c;
}
int _unsetenv(const char *name)
{
	char *env;
	int i = 0;

	env = _getenv(name);
	if(env == NULL)
		return (0);
	while (strcmp(strtok(environ[i],"="), name) != 0)
		i++;
	while (environ[i] != NULL)
	{
		if(environ[i + 1])
		   swap(_getenv(environ[i]), _getenv(environ[i + 1]));
		else
			environ[i] = NULL;
		i++;
	}
	return (0);
}
int main(int argc, char **argv)
{
	if(argc !=2)
	{
		printf("Usage: ./unsetenv <env>\n");
		exit(1);
	}
	printf("%s %s %d\n", argv[1], _getenv(argv[1]), getpid());
	sleep(10);
	_unsetenv(argv[1]);
	sleep(10);
	return (0);
}
