#include "shell.h"
char **tokenize_and(char *input)
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

	token = strtok(input, "&&");
	while (token != NULL)
	{
		tokens[token_count] = _strdup(token);
		if (tokens[token_count] == NULL)
		{
			perror("strdup");
			exit(1);
		}
		token_count++;
		token = strtok(NULL, "&&");
	}
	free_str(token);
	tokens[token_count] = NULL;
	return (tokens);
}

int handle_operators(char **commands, char *copy)
{
	if (_strchr(copy, ';'))
	{
		printf("%s\n", copy);
		execute(commands);
		return (0);
	}
	else if (_strchr(copy, '&'))
	{
		printf("%s\n", copy);
		execute_and(commands);
	}
	else
	{
		return (0);
	}
	return (0);
}


int execute_or(char **commands)
{
	int status;
	int i = 0, success_status = 0;
	char **av = NULL;
	char *first = NULL;
	pid_t child_pid;

	while (commands[i] != NULL)
	{
		av = _strtok(commands[i], " ");
		if (check_inbuilts(av[0]) == 1)
		{
			handle_builtins(av, commands[i]);
		}
		else
		{
			first = get_exe(av[0]);
			if (first == NULL)
			{
				first = strdup(av[0]);
			}
			child_pid = fork();
			if (child_pid == 0)
			{
				if (execve(first, av, environ) == -1)
				{
					printf("%s: command not found\n", av[0]);
				}
			}
			else
			{
				wait(&status);
				if (status == 0)
				{
					success_status = 1;
					reset(&av, &commands[i], &first);
					free_sarray(commands);
					break;
				}
			}
		}
		reset(&av, &commands[i], &first);
		i++;

	}
	return (success_status);
}
