#include "shell.h"

/**
 * executables - Function that checks for executables.
 * @input: Pointer to the string to which the executable is checked.
 *
 * Return: -1 upon failure.
 */

int executables(char *input)
{
	char *check = input;
	int i;
	struct stat Stat;

	for (i = 0; check[i]; i++)
	{
		if (check[i] == '.')
		{
			if (check[i + 1] == '.')
				return (0);
			else if (check[i + 1] == '/')
				continue;
		}
		else if (check[i] == '/' && i != 0)
		{
			if (check[i + 1] == '.')
				continue;

			i++;
			break;
		}
		else
			break;
	}

	if (i == 0)
		return (0);

	if (stat(input + i, &Stat) == 0)
		return (i);

	return (-1);
}

/**
 * Which - Search for a command in the directories listed in the Path
 * environment variable.
 * @input: The command to search for.
 *
 * Return: A pointer to the full path of the command if found, else Null
 */

char *Which(char *input)
{
	char *path, *copy, *tok;
	char *dir;
	int string_len;
	struct stat Stat;

	path = Strdup(getenv_custom("PATH"));
	copy = path;
	tok = _strtok(copy, ":");

	while (tok)
	{
		string_len = Strlen(input) + Strlen(tok) + 2;
		dir = malloc(string_len * sizeof(char));
		if (!dir)
		{
			free(dir);
			return (NULL);
		}
		dir = Strcpy(dir, tok);
		dir = Strcat(dir, "/");
		dir = Strcat(dir, input);
		dir = Strcat(dir, "\0");
		if (stat(dir, &Stat) == 0)
		{
			free(path);
			return (dir);
		}
		else
		{
			free(dir);
			tok = _strtok(NULL, ":");
		}
	}
	if (stat(input, &Stat) == 0)
	{
		free(path);
		return (Strdup(input));
	}
	free(path);
	return (NULL);
}


/**
 * Access - Check if a command is accessible and executable.
 * @input: The command to check.
 * @shell: Pointer to the shell data structure.
 *
 * Return: ) on success, -1 if the command is not accessible.
 */

int Access(char *input, SHELL *shell)
{
	if (input == NULL)
	{
		/*print error to the console*/
		Command_unfound(shell);
		shell->status = 127;
		return (-1);
	}

	else if (access(input, X_OK) == -1)
	{
		/*print error to the console*/
		path_error(shell);
		return (-1);
	}

	return (0);
}
/**
 * Syntax - check the syntax of a command for correctness.
 * @input: The command to check for syntax.
 * @shell: Pointer to the shell data structure.
 *
 * Return: 0 on success, -1 if there is a syntax error.
 */

int Syntax(char *input, SHELL *shell)
{
	if (First(input, shell) == -1 || Syntax_error(input, shell) == -1)
	{
		return (-1);
	}

	return (0);

}

/**
 * First - Check the syntax of the first token in the command.
 * @input: The command to check for the first token.
 * @shell: Pointer to the shell data structure.
 *
 * Return: 1 on success, -1 if there is a syntax error.
 */

int First(char *input, SHELL *shell)
{
	int i;
	char *Error_txt = NULL;

	for (i = 0; input[i]; i++)
	{
		while (input[i] == ' ' || input[i] == '\t')
		{
			i++;
		}

		if (input[i] == ';')
		{
			Error_txt = (input[i + 1] == ';' ? ";;" : ";");
			break;
		}

		else if (input[i] == '|')
		{
			Error_txt = (input[i + 1] == '|' ? "||" :  "|");
			break;
		}

		else if (input[i] == '&')
		{
			Error_txt = (input[i + 1] == '&' ? "&&" : "&");
			break;
		}

		else
		{
			break;
		}
	}
	if (Error_txt)
	{
		write_error(Error_txt, shell);
		return (-1);
	}
	return (1);
}

