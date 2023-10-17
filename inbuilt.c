#include "shell.h"

/**
 *global_var - checks for eviroment variables
 *@input: the input strig
 *@shell: the main struct
 *Return: an intergrated string
 */

char *global_var(char *input __attribute__ ((unused)), SHELL *shell)
{
	char *status, *id;
	int i;

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
			{
				status = Itoa(shell->status);
				return (exit_status(input, status));
			}

			else if (input[i + 1] == '$')
			{
				id = Itoa(shell->pid);
				return (identity(input, id));
			}

			else
			{
				return (En_var(input, shell));
			}
		}
	}


	return (input);
}

/**
 *exit_status - handles printig of the exit status
 *@input: the iiput string
 *@status: the status string
 *Return: the strings combined
 */

char *exit_status(char *input, char *status)
{
	int i, len, j, l;
	char *new;

	len = (Strlen(input) + Strlen(status));
	new = malloc(len + 1);

	if (!new)
	{
		Write("MEMORY ALLOCATION FAILURE\n");
		exit(EXIT_FAILURE);
	}

	for (i = j = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			for (l = 0; l < Strlen(status); l++)
			{
				new[j] = status[l];
				j++;
			}
			i++;
		}

		else
		{
			new[j] = input[i];
			j++;
		}
	}

	new[j] = '\0';
	free(status);
	free(input);
	return (new);
}

/**
 *identity - handles the pid
 *@input: the string input
 *@id: the string id
 *Return: a string with the id intergrated
 */

char *identity(char *input, char *id)
{
	int i, len, j, l;
	char *new;

	len = (Strlen(input) + Strlen(id));
	new = malloc(len + 1);

	if (!new)
	{
		Write("MEMORY ALLOCATION FAILURE\n");
		exit(EXIT_FAILURE);
	}

	for (i = j = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			for (l = 0; l < Strlen(id); l++)
			{
				new[j] = id[l];
				j++;
			}
			i++;
		}

		else
		{
			new[j] = input[i];
			j++;
		}
	}

	new[j] = '\0';
	free(id);
	free(input);
	return (new);
}

/**
 *En_var - handles enviroment variables
 *@input: the string input
 *@shell: the mai struct
 *Return: a string with the enviroment variable  integrated
 */

char *En_var(char *input, SHELL *shell __attribute__ ((unused)))
{
	char *ename, *copy, *new;
	int len;

	ename = input, copy = NULL;
	while (*ename)
	{
		if (*ename == '$')
		{
			break;
		}
		ename++;
	}
	ename = _strtok(ename, " \n");
	if (!*(ename + 1))
	{
		copy = "$";
	}
	else
	{
		ename++;
		copy = getenv_custom(ename);
	}
	if (copy)
	{
		len = Strlen(input) + (Strlen(copy) - Strlen(ename));
		new = malloc((len + 1) * sizeof(char));
	}
	else
	{
		new = malloc((Strlen(input) + 1) * sizeof(char));
	}
	if (!new)
	{
		exit(EXIT_FAILURE);
	}
	return (replacer(input, new, copy, (*ename == '$' ? ename : ename - 1)));
}

/**
 *replacer - where the swappiong takees place
 *@input: the input string
 *@new: the new mallocated string
 *@ename: the name be replaced
 *@copy: the enviroment variable to copy
 *Return: an itergrated string
 */

char *replacer(char *input, char *new, char *copy, char *ename)
{
	int i, j, k;

	if (copy)
	{
		for (i = j = 0; input[i]; i++)
		{
			if (input[i] == '$')
			{
				for (k = 0; copy[k]; k++)
				{
					new[j] = copy[k];
					j++;
				}
				i += Strlen(ename);
			}
			else
			{
				new[j] = input[i];
				j++;
			}
		}
	}
	else if (copy == NULL)
	{
		for (i = j = 0; input[i]; i++)
		{
			if (input[i] == '$')
			{
				i += Strlen(ename);
			}
			else
			{
				new[j] = input[i];
				j++;
			}
		}
	}
	new[j] = '\0';
	free(input);
	return (new);
}
