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

char **str_array(char *path, char *delim)
{
	char **paths = NULL;
	int i = 0;
	int no = 0;

	if (path)
	{
		while(path[i])
		{
			if (path[i++] == delim[0])
				no++;
		}
		paths = malloc(sizeof(char *) * (no + 1));
		i = 0;
		paths[i++] = strdup(strtok(path, delim));
		while( i <= no)
		{
			paths[i++] = strdup(strtok(NULL, delim));
		}
		paths[i] = NULL;
	}

	return (paths);
}

int main(void)
{
	char *PATH, **dirs = NULL;
	int i  = 0;

	PATH = _getenv("PATH");
	dirs = str_array(PATH, ":");
	while (dirs[i])
		printf("%s\n", dirs[i++]);
	return (0);
}
