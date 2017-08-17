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

int _setenv(const char *name, const char *value, int overwrite)
{
	int  cnt = 0, i = 0;
	char **envp, *env;
	static int first  = 1;

	if (name != NULL)
	{
		env = _getenv(name);
		if(env != NULL)
		{
			if (!overwrite)
				return (0);
			if (strlen(env) >= strlen(value))
			{
				while (( *env++ = *value++));
				return (0);
			}
			else
			{
				strcpy(env, value);
				return (0);
			}
		}
		else
		{
				/* putenv */
			cnt = strlen(name) + strlen(value) + 2;
			env = malloc(sizeof(char) * cnt);
			if (env == NULL)
				return (-1);
			memset (env , '\0' , cnt);
			strcpy(env, name);
			strcat(env, "=");
			strcat(env, value);
			while (environ[i] != NULL) i++;
			if (first)
			{
				envp = (char **) malloc(sizeof(char *) * (i + 2));
				if (envp == NULL)
					return(-1);
				first = 0;
				(void) memcpy(envp, environ, sizeof(char *) * i);
			} else
			{
				envp = (char **) realloc((char *)environ, sizeof(char *) * (i + 2));
				if (envp == NULL)
					return(-1);
			}
			environ = envp;
			environ[i] = strdup(env);
			environ[i+1] = NULL;
			return (0);
		}
	}
	return (-1);
}

int main(int argc, char **argv)
{
	int overwrite = 1;

	if(argc != 3)
	{
		printf("Usage: ./setenv <env name> <env value>\n");
		exit(1);
	}
	if(_getenv(argv[1]) == NULL)
		overwrite = 0;
	printf("%s -> %s %d\n", argv[1], getenv(argv[1]), getpid());
	sleep(10);
	if(_setenv(argv[1], argv[2] , overwrite) >= 0)
		printf("%s -> %s %d\n", argv[1], getenv(argv[1]), getpid());
	sleep(10);
	return (0);
}
