#include "shell.h"
void resset(char token[10])
{
	int i = 0;

	while (token[i])
	{
		token[i] = 0;
		i++;
	}
}
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


char **tokenize(char *input)
{
	char **tokens;
	int i = 0, token_count = 0;
	char *token;

while (input[i])
{
	if (input[i] == '\n')
	{
		input[i] = '\0';
	}
	i++;
}

if (input == NULL)
{
	return (NULL);
}

tokens = malloc(strlen(input) * sizeof(char *));

if (tokens == NULL)
{
	perror("malloc");
	exit(1);
}

token = strtok(input, "||");
while (token != NULL)
{
	tokens[token_count] = _strdup(token);
	if (tokens[token_count] == NULL)
	{
		perror("strdup");
		exit(1);
	}
	token_count++;
	token = strtok(NULL, "||");
}
free_str(token);
tokens[token_count] = NULL;
return (tokens);
}
