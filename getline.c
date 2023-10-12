#include "shell.h"

/**
 * free_sarray - frees an array of strings
 * @av: the array to free
 * Return: 0 on success
 */
void free_sarray(char **av)
{
	if (av != NULL)
	{
		int i = 0;

		/*printf("not null. freeing\n");*/

		while (av[i] != NULL)
		{
			free(av[i]);
			i++;
		}
		free(av);
	}
	return;
}

/**
 * free_str - frees a string
 * @str: a string allocated memory by malloc
 * Return: nothing
 */
void free_str(char *str)
{
	if (str != NULL)
	{
	/*	printf("%s is not null, freeing\n", str);*/
		free(str);;
	}
	return;
}
/**
 * whitespace - checks for white spaces
 * @command: command input
 * Return 0 is command consist of whitespaces
 */
int whitespace(char *command)
{
	int i;
	int count = 0;
	int len;

	len = strlen(command);
	for (i = 0; i < len; i++)
	{
		if (command[i] == ' ' || command[i] == '\t' || command[i] == '\n')
			count++;
		else
			return (0);
	}
	return (1);
}


