#include "shell.h"
/**
 * **tokenize_separator - tokenizes with delimiter as command separator
 * @input: command line
 * Return: the tokens in an array
 */

char **tokenize_separator(char *input)
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

	token = strtok(input, ";");
	while (token != NULL)
	{
		tokens[token_count] = _strdup(token);
		if (tokens[token_count] == NULL)
		{
			perror("strdup");
			exit(1);
		}
		token_count++;
		token = strtok(NULL, ";");
	}
	free_str(token);
	tokens[token_count] = NULL;
	return (tokens);
}
/**
 * free_sarray - frees an array of strings
 * @av: the array to free
 * Return: 0 on success
 */
void free_sarray(char **av)
{
	int i;

	if (av != NULL)
	{
		i = 0;
		/*printf("not null. freeing\n");*/

		while (av[i] != NULL)
		{
			if (av[i] != NULL)
			{
				free(av[i]);
			}
			i++;
		}
		free(av);
	}
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
		free(str);
	}
}
/**
 * whitespace - checks for white spaces
 * @command: command input
 * Return: 0 is command consist of whitespaces
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

/**
 * tokenize - tokenizes input with logical operators and command separator
 * @input: input
 * Return: array of tokens
 */

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
