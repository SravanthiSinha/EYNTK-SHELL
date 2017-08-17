#include <stdio.h>
#include <malloc.h>

/**
 * strtok - Function that tokenizes the string
 * @str: string to be tokensed
 * @delimeter: delimeter to be used for tokenizing
 * Return: one token @ every call
 */
char *strtok(char *str, const char *delimeter)
{
	static char *lasts;
	int  j = 0, len = 0, k = 0;
	char *token = NULL;

	if (str == 0)
		str = lasts;
	while (str[len] && delimeter[j] && str[len] != delimeter[j])
	{
		len++;
		if (str[len] == delimeter[j])
			j++;
	}
	token = malloc(sizeof(char) * (len + 1));
	j = 0;
	while (j < len)
	{
		token[j] = *lasts;
		*lasts = *(str++);
		j++;
	}
	token[len] = '\0';
	return (token);
}

/**
 * main - using strrok
 * Return: Always 0
 */
int main(void)
{
	char str[80] = "Roses are red";
	const char s[2] = " ";
	char *token;

	/* get the first token */
	token = strtok(str, s);

	/* walk through other tokens */
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, s);
	}
	return (0);
}
