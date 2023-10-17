#include "shell.h"
/**
 * _chdir - change directories
 * @av: array of strings containing command cd and its arguments
 * Return: 0 on success and 1 on failure
 */

int _chdir(char **av);
int _chdir(char **av)
{
	char *newDir = NULL;
	char *prevDir = NULL;
	char *dir = NULL;
	int i = 0;

	while (av[i])
	{
		i++;
	}

	if (i > 1)
	{

		if (_strcmp(av[1], "-") == 0)
		{
			dir = getenv("OLDPWD");
			if (dir == NULL)
			{
				perror("cd: OLDPWD not set\n");
				return (1);
			}
		}
		else
			dir = av[1];
	}
	else
	{
		dir = getenv("HOME");
		if (dir == NULL)
		{
			perror("cd: HOME not set\n");
			return (1);
		}
	}
	prevDir = getcwd(NULL, 0);

	if (prevDir == NULL)
	{
		perror("getcwd");
		return (1);
	}
	if (chdir(dir) != 0)
	{
		perror("chdir");
		free(prevDir);
		return (1);
	}
	if (setenv("PWD", getcwd(NULL, 0), 1) != 0)
	{
		perror("setenv");
		free(prevDir);
		return (1);
	}
	newDir = getcwd(NULL, 0);

	if (newDir == NULL)
	{
		perror("getcwd");
		free(prevDir);
		return (1);
	}
	printf("%s\n", newDir);
	free(newDir);
	free(prevDir);
	return (0);
}
/**
 * _setenv - sets enviroment variables using the built in command
 * @name: name of the envirment
 * @value: value to be placed under name
 * @overwrite: overwrite status
 *
 * Return: 0 on success, -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{

	if (getenv(name) != NULL && !overwrite)
	{
		perror("getenv");
		return (-1);
	}


	if (setenv(name, value, 1) != 0)
	{
		perror("setenv");
		return (-1);
	}

	return (0);
}
/**
 * _unsetenv - unsets an existing environment
 * @name: name of the environment to unset
 *
 * Return: 0
 */

int _unsetenv(const char *name)
{

	if (unsetenv(name) != 0)
	{
		perror("unsetenv");
		return (-1);
	}

	return (0);
}
/**
* handle_builtins - handles the exit and env inbuilts
* @av: array of stringscommandline argument
* @command: commnad
* Return: (0)
*/
int handle_builtins(char **av, char *command)
{
	if (_strcmp(av[0], "exit") == 0)
	{
		if (av[1])
		{
			int status;

			status = atoi(av[1]);
			free_str(command);
			free_sarray(av);
			exit(status);
		}
		else
		{
			free_str(command);
			free_sarray(av);
			exit(0);
		}
	}
	else if (_strcmp(av[0], "setenv") == 0)
	{
		if (av[1] != NULL && av[2] != NULL)
		{
			if (_setenv(av[1], av[2], 1))
				printf("setenv: command not found\n");
		}
	}
	else if (_strcmp(av[0], "unsetenv") == 0)
	{
		if (av[1] != NULL)
			_unsetenv(av[1]);
		else
			printf("setenv: command not found\n");
	}
	else if (_strcmp(av[0], "cd") == 0)
	{
		chdir(av[1]);
	}
	else if (_strcmp(av[0], "alias") == 0)
	{
		handle_alias(av);
	}
	return (0);
}
