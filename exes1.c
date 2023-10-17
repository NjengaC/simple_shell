#include "shell.h"

#define ARRAY_SIZE 128

/**
 * tokenize - Split a line into tokens based on the specified mode.
 * @line: The line to be tokenized.
 * @mode: the mode of tokenization ie 1 for normal, 2 for special
 * characters.
 *
 * Return: A dynamically allocated array of strings containing the tokens,
 * or NULL if an error occured.
 */

char **tokenize(char *line, int mode)
{
	char **word_t, *word;
	int size = ARRAY_SIZE, i = 0;
	char *Del;

	if (line == NULL)
	{
		perror("hsh");
		return (NULL);
	}
	if (mode == 1)
	{
		Del = " \n";
	}
	else
	{
		Del = "|&;";
	}
	word_t = malloc(size * sizeof(char *));
	if (word_t == NULL)
	{
		free(word_t);
		return (NULL);
	}
	word = strtok(line, Del);
	while (word != NULL)
	{
		if (i == size - 1)
		{
			word_t = Realloc(word_t, size * sizeof(char *), size * 2 * sizeof(char *));
			if (!word_t)
			{
				write(STDERR_FILENO, "MEMORY ALLOCATION ERROR\n", 24);
				exit(EXIT_FAILURE);
			}
			size = size * 2;
		}
		word_t[i] = strdup(word), word = strtok(NULL, Del), i++;
	}
	word_t[i] = NULL;
	return (word_t);
}

/**
 * Syntax_error - Check for syntax errors in the command.
 * @input: The command to check for syntax errors.
 * @shell: Pointer to the shell data structure.
 *
 * Return: 0 on success, -1 if a syntax error is present.
 */

int Syntax_error(char *input, SHELL *shell)
{
	int i;
	char *error_txt;

	error_txt = NULL;
	i = 1;

	for (; input[i]; i++)
	{
		if (input[i] == ';')
		{
			if (input[i + 1] == ';')
			{
				error_txt = ";;";
				break;
			}

			else if (input[i + 1] == '|')
			{
				error_txt = "|";
				break;
			}

			else if (input[i + 1] == '&')
			{
				error_txt = "&";
				break;
			}
		}
	}
	if (error_txt)
	{
		write_error(error_txt, shell);
		return (-1);
	}
	else if (Pipe(input, shell) == -1 || ampersand(input, shell) == -1)
	{
		return (-1);
	}

	return (0);
}

/**
 * Pipe - Check for syntax errors retated to pipes in command.
 * @input: the command to check for pipe-related syntax errors.
 * @shell: Pointer to the shell data structure.
 *
 * Return: 0 on success, -1 if a syntax error is encountered.
 */

int Pipe(char *input, SHELL *shell)
{
	int i;
	char *error_txt = NULL;

	for (i = 1; input[i]; i++)
	{
		if (input[i] == '|' && input[i + 1] == '|')
		{
			i += 2;
		}

		if (input[i] == '|')
		{
			if (input[i + 1] == ';')
			{
				error_txt = (input[i + 2] == ';' ? ";;" : ";");
				break;
			}

			else if (input[i + 1] == '&')
			{
				error_txt = (input[i + 2] == '&' ? "&&" : "&");
				break;
			}

			else if (input[i] == '|')
			{
				i++;
				error_txt = (input[i + 1] == '|' ? "||" : "|");
				break;
			}
		}
	}

	if (error_txt)
	{
		write_error(error_txt, shell);
		return (-1);
	}

	return (0);
}

/**
 * ampersand - Check for syntax errors related to ampersands in the command.
 * @input: the command to check for ampersand-related syntax errors.
 * @shell: Pointer to the shell data structure.
 *
 * Return: 0 on success, -1 if a syntax error is encountered.
 */

int ampersand(char *input, SHELL *shell)
{
		int i;
	char *error_txt = NULL;

	for (i = 1; input[i]; i++)
	{
		if (input[i] == '&' && input[i + 1] == '&')
		{
			i += 2;
		}

		if (input[i] == '&')
		{
			if (input[i + 1] == ';')
			{
				error_txt = (input[i + 2] == ';' ? ";;" : ";");
				break;
			}

			else if (input[i + 1] == '|')
			{
				error_txt = (input[i + 2] == '|' ? "||" : "|");
				break;
			}

			else if (input[i] == '&')
			{
				i++;
				error_txt = (input[i + 1] == '&' ? "&&" : "&");
				break;
			}
		}
	}

	if (error_txt)
	{
		write_error(error_txt, shell);
		return (-1);
	}

	return (0);
}
/**
 * exit_command - exits shell
 * @shell: the main struct
 * Return: nothing
 */


void exit_command(SHELL *shell)
{
	int exit_status;

	if (shell->toks[1] != NULL)
	{
		exit_status = Atoi(shell->toks[1]);
		shell->status = exit_status;
		exit(shell->status);
	}
	else
	{
		shell->status = 0;
		exit(shell->status);
	}
}
