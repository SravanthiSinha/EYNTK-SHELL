#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char**argv, char **env)
{
	printf("environ address : %p\n", (void*)environ);
	printf("envp address : %p\n", (void*)env);

	return (0);
}
