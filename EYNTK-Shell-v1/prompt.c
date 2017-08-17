#include <stdio.h>
#include <stdlib.h>

/**
 * main - Read line
 *
 * Return: Always 0.
 */
 int main(void)
 {
     char* line = NULL;
     size_t len = 0;
     ssize_t read;
     size_t i = 0;

     printf("$ ");

     while ((read = getline(&line, &len, stdin))>0)
     {
	     do{
		     printf("%c", line[i++]);
	     }while(line[i] != '\n');

	     if(line[i] == '\n')
		     break;

	     i = 0;
     }
     printf("\n");
     free(line);
     return 0;
 }
