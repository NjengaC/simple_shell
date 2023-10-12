#include "shell.h"
/**
 * reset - resets variables and returns wait status
 * @argv: commandline args and their flags
 * @full_path - full path
 * @command: specific commands as taken by getline
 * @count: track to the arguments
 *
 * Return: 0
 */
int reset(char ***argv, char **first, char **command, int *count)

{
	free_sarray(*argv);
/*	free_str(*full_path);*/
	free_str(*command);
	free_str(*first);
	*argv = NULL;
	*command = NULL;
	*first = NULL;
/*	*full_path = NULL;*/
	*count = 0;

	return (0);
}
/**
 * _strtok - breaks string into an array of null-terminated strings(tokena)
 * @input: a string (command arguments)
 * Return: an array on null-terminated strings
 */

char **_strtok(char *input, const char *delim)
{
	char **tokens;
	char *token;
	int token_count;
	
	tokens = malloc(strlen(input) * sizeof(char *));

	if (tokens == NULL)
	{
		perror("malloc");
		exit(1);
	}

	token = NULL;
	token_count = 0;

	token = strtok(input, delim);
	while (token != NULL)
	{
		tokens[token_count] = _strdup(token);
		if (tokens[token_count] == NULL)
		{
			perror("strdup");
			exit(1);
		}
		token_count++;
		token = strtok(NULL, delim);
	}
	free_str(token);
	tokens[token_count] = NULL;
	return (tokens);
}
/**
 * get_exe - gets the full PATH for specified executable
 * @command: command for whose exe we are getting
 * Return: returns the full path
 */
char *get_exe(char *command)
{
	char path[] = SHELL_PATH;
	char *token;
	char *full_path;

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
		{
			full_path = (strdup(command));
			return (full_path);
		}
		else
		{
			return (NULL);
		}
	}
	else
	{
		token = strtok(path, ":");
		while (token != NULL)
		{
			full_path = malloc(strlen(token) + strlen(command) + 2);
			if (full_path == NULL)
			{
				perror("malloc");
				exit(1);
			}
			strcpy(full_path, token);
			strcat(full_path, "/");
			strncat(full_path, command, strlen(command) + 1);
	/*		full_path[strlen(full_path)] = '\0';*/

			if (access(full_path, X_OK) == 0)
			{
				return (full_path);
			}
			else
			{
				free_str(full_path);
			}
			token = strtok(NULL, ":");
		}
	}
	return (NULL);
}
/**
 * check_inbuilts - checks and handles inbuilt command arguments
 * @input: string to check
 * Return: 1 if one exists or 0 if none
 */
int check_inbuilts(char *input)
{
	if (_strcmp(input, "exit") == 0 || _strcmp(input, "setenv") == 0)
	{
		return (1);
	}
	else if (_strcmp(input, "unsetenv") == 0 || _strcmp(input, "cd") == 0)
	{
		return (1);
	}
return (0);

}
/**
 * main - entry point for the command line interpreter, displays a prompt
 * and waits for the user to type a command
 * Return: 0 On success
 */
int main(void);
int main(void)
{
	char *command = NULL;
	int status, i;
	char **av = NULL;
	char *first = NULL;
	/*char **commands = NULL;*/
	ssize_t read;
	size_t len = 0;
	pid_t child_pid;

	while (1)
	{
		printf("$ ");
		read = getline(&command, &len, stdin);

		if (feof(stdin) || (read == -1))
		{

			printf("\n");
			break;
		}
		if ((whitespace(command)) == 1)
		{
			printf("\n");
		}
		else
		{
				av = _strtok(command, " \t\n");
				if (av[0])
				{
					if ((check_inbuilts(av[0])) == 1)
					{
						handle_builtins(av, command);
					}
					else
					{
						first = get_exe(av[0]);
						if (first == NULL)
							first = strdup(av[0]);

						child_pid = fork();
						if (child_pid == 0)
						{
							if (execve(first, av, environ) == -1)
							{
								printf("%s :command not found\n", av[0]);
								reset(&av, &command, &first, &i);
								exit(0);
							}
						}
						else
						{
							reset(&av, &command, &first, &i);
							wait(&status);
							if (status != 0)
							{
								printf("Fork failed\n");
								exit (0);
							}
						}
					}
				}
			/*reset(&av, &command, &first, &i);*/
		}
		reset(&av, &command, &first, &i);
	}
		/*reset(&av, &command, &first, &i);*/
	free_sarray(av);
	free_str(command);
	free_str(first);

	return (0);
}
