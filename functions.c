#include "shell.h"

/**
 *change_dir_command - changes directories
 *@shell: the main struct
 *Return: nothing
 */
void change_dir_command(SHELL *shell)
{
	int result;
	char cwd[1024];
	const char *oldpwd;

	if (!shell->toks[1] || Strcmp(shell->toks[1], "~") == 0)
	{
		result = chdir(getenv_custom("HOME"));
	}
	else if (Strcmp(shell->toks[1], "-") == 0)
	{
		oldpwd = getenv_custom("OLDPWD");
		if (oldpwd[0] == '\0')
		{
			perror("hsh");
			return;
		}
		result = chdir(oldpwd);
	}
	else
	{
		result = chdir(shell->toks[1]);
	}

	if (result == -1)
	{
		perror(shell->av[0]);
		return;
	}
	else if (result != -1)
	{
		getcwd(cwd, sizeof(cwd));
		setenv("OLDPWD", getenv_custom("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
}
/**
 *env_extract - extracts enviroment varaibles
 *@shell: the main struct
 *Return: void
 */

void env_extract(SHELL *shell)
{
	int env_count = 0, i, j;

	while (environ[env_count] != NULL)
		env_count++;
	shell->_environ = malloc(sizeof(char *) * (env_count + 1));
	if (!shell->_environ)
		return;
	for (i = 0; i < env_count; i++)
	{
		shell->_environ[i] = Strdup(environ[i]);
		if (!shell->_environ[i])
		{
			for (j = 0; j < i; j++)
				free(shell->_environ[j]);
			free(shell->_environ);
			return;
		}
	}
	shell->_environ[env_count] = NULL;
}
/**
 *Command_unfound -  prints the command unfoud error
 *@shell: the main struct
 *Return: nothing
 */

void Command_unfound(SHELL *shell)
{
	char *loop_count;

	loop_count = Itoa(shell->loop_count);
	Write(shell->av[0]);
	Write(": ");
	Write(loop_count);
	Write(": ");
	Write(shell->toks[0]);
	Write(": not found\n");

	free(loop_count);
}

/**
 *path_error - prints the path error
 *@shell: the main struct
 *Return: nothing
 */

void path_error(SHELL *shell)
{
	char *loop_count;


	loop_count = Itoa(shell->loop_count);

	Write(shell->av[0]);
	Write(": ");
	Write(loop_count);
	Write(": ");
	Write(shell->toks[0]);
	Write(": Permission denied\n");

	free(loop_count);
}

/**
 *write_error - writes error to thr console
 *@error: the errror to be printed
 *@shell: the main struct
 *Return: nothhig
 */

void write_error(char *error, SHELL *shell)
{
	char *count = Itoa(shell->loop_count);

	Write(shell->av[0]);
	Write(": ");
	Write(count);
	Write(": ");
	Write("Syntax error");
	Write(": \"");
	Write(error);
	Write("\" unexpected\n");

	free(count);
}
