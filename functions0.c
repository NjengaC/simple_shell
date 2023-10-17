#include "shell.h"
/**
 * _strchr - function checks occurence of a character
 * @s: name of string containing character
 * @c: character to locate
 *
 * Return: 0 on (Success) else return the character
 */

int _strchr(char *s, char c)

{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{

	return (write(1, &c, 1));
}
/**
 * _strdup - duplicate content of a string
 * @str: string to duplicate
 * Return: duplicated string
 */
char *_strdup(const char *str)
{
	ssize_t len = strlen(str);
	char *duplicate;

	if (str == NULL)
	{
		return (NULL);
	}

	duplicate = malloc(len + 1);
	if (duplicate == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (duplicate != NULL)
	{
		strcpy(duplicate, str);
	}
	return (duplicate);
}

/**
 * execute_and - executes command with logical &
 * @commands: commands
 * Return: 0 on succes
 */
int execute_and(char **commands);
int execute_and(char **commands)
{
	int status;
	int i = 0, success_status = 0, exec_failed;
	char **av = NULL;
	char *first = NULL;
	pid_t child_pid;

	while (commands[i] != NULL)
	{
		av = _strtok(commands[i], " ");
		if (av[0])
		{
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

				exec_failed = 0;

				child_pid = fork();
				if (child_pid == 0)
				{
					if (execve(first, av, environ) == -1)
					{
						exec_failed = 1;
						printf("%s: command not found\n", av[0]);
					}
					exit(exec_failed);
				}
				else
				{
					wait(&status);
					if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
					{
						reset(&av, &commands[i], &first);
						break;
					}
					else
					{
						success_status = 1;
					}
				}
			}
			reset(&av, &commands[i], &first);
		}
		i++;
		if (!success_status)
		{
			break;
		}
	}
	i++;
	while (commands[i] != NULL)
	{
		if (commands[i] != NULL)
		{
			free_str(commands[i]);
		}
		i++;
	}

	if (commands != NULL)
	{
		free_sarray(commands);
	}

	return (0);
}
