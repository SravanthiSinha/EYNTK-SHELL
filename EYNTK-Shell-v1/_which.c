#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

char *get_path(char *envp[])
{
	char *absolute_path = NULL;
	int i = 0;

	while(envp[i])
	{
		if(strcmp(strndup(envp[i], 4), "PATH") == 0)
		{
			absolute_path = envp[i] + 4;
			break;
		}
		i++;
	}
	return (absolute_path);
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


int main(int argc, char**argv, char *envp[])
{
	int j = 1, i = 0;
	char **absolute_paths = NULL,  **filenames = NULL;

	if(argc < 2)
	{
		printf("Usage: _which filename ...\n");
		exit(1);
	}

	absolute_paths = str_array(get_path(envp)+1 , ":");
	while(absolute_paths && absolute_paths[i] && argv[j])
	{
		filenames = str_array(strrev(strdup(absolute_paths[i])), "/");
		if (strcmp(strrev(filenames[0]), argv[j]) == 0)
		{
			printf("%s Found\n", argv[j]);
			j++;
		}
		else
		{
			if(absolute_paths[i + 1] == NULL)
			{
				printf("%s Not Found\n", argv[j]);
				j++;
				i = 0;
			}
		}
		free(filenames);
		i++;
	}
	return (0);
}
