#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

typedef struct List
{
	char *str;
	struct List *next;
} List;

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

int add_node(List **list, char *str)
{
	List *tmp, *node;

	if (list == NULL)
		return (EXIT_FAILURE);
	tmp = malloc(sizeof(List));
	if(tmp == NULL)
		return (EXIT_FAILURE);
	tmp->str = strdup(str);
	if(*list == NULL)
	{
		tmp->next = NULL;
		*list = tmp;
	}
	else
	{
		node = *list;
		while(node->next)
		{
			node = node->next;
		}
		tmp->next = NULL;
		node->next = tmp;
	}
	return (EXIT_SUCCESS);
}
void array_to_list(List **list, char **dirs)
{
	int i = 0, k = EXIT_SUCCESS;

	if (dirs == NULL)
		return;
	while(dirs[i] && k == EXIT_SUCCESS)
		k = add_node(list, dirs[i++]);
}

void print_list(List *list)
{
	List *node;

	if(list != NULL)
	{
		node = list;
		while(node)
		{
			printf("%s\n", node->str);
			node =node->next;
		}
	}
}
int main(void)
{
	char *PATH, **dirs = NULL;
	int i  = 0;
	List *list = NULL;

	PATH = _getenv("PATH");
	dirs = str_array(PATH, ":");
	array_to_list(&list, dirs);
	print_list(list);
	return (0);
}
