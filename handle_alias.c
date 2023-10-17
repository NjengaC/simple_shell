#include "shell.h"

/**
 *process - processees the commands for forking or execution
 *@shell: the mai struct
 *Return: nothing
 */

int process(SHELL *shell)
{
	int Exec, i, numbuilts;
	char *Dir,  *bul = shell->toks[0], *builtin[] = {"cd", "exit"};

	Exec = executables(shell->toks[0]);

	numbuilts = sizeof(builtin) / sizeof(builtin[0]);
	for (i = 0; i < numbuilts; i++)
	{
		if (Strcmp(bul, builtin[i]) == 0)
			return (0);
	}
	if (Exec == -1)
	{
		Command_unfound(shell);
		shell->status = 127;
		return (1);
	}
	else if (Exec == 0)
	{
		Dir = Which(shell->toks[0]);
	}
	else
	{
		Dir = shell->toks[0] + Exec;
	}
	if (Access(Dir, shell) == -1)
	{
		shell->status = 126, free(Dir);
		return (1);
	}
	Fork(Dir, shell);
	if (Exec == 0)
	{
		free(Dir);
	}
	return (0);
}

/**
 *Fork - performs the executio of the command
 *@input: the path of the executable
 *@shell: the mai struct
 */

void Fork(char *input, SHELL *shell)
{
	pid_t Pid;
	int state;
	char **tok;


	Pid = fork();
	tok = shell->toks;

	if (Pid == 0)
	{
		execve(input, tok, environ);
	}

	else if (Pid < 0)
	{
		perror(tok[0]);
		return;
	}

	else
	{
		do {
			waitpid(Pid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shell->status = state / 256;
}
/**
 *handle_file - handles commands in a file
 *@shell: main struct
 *Return: nothing
 */

void handle_file(SHELL *shell)
{
	FILE *reads;
	size_t len;
	char *line = NULL;


	reads = fopen(shell->av[1], "r");

	if (reads == NULL)
	{
		exit(EXIT_FAILURE);
	}

	while ((getline(&line, &len, reads)) != -1)
	{
		shell->loop_count++;
		source(shell, line);
	}
	if (line)
	{
		free(line);
	}

	fclose(reads);
	exit(0);
}
/**
 *Frees - frees the main struct
 *@eshell: the main struct
 *Return: void
 */

void Frees(SHELL *eshell)
{
	int j;

	if (eshell->toks)
	{
		for (j = 0; eshell->toks[j]; j++)
		{
			free(eshell->toks[j]);
		}

		free(eshell->toks);
	}

	for (j = 0; eshell->_environ[j]; j++)
	{
		free(eshell->_environ[j]);
	}

	free(eshell->_environ);

	eshell->toks = NULL;
}

/**
 *Free_log - frees the logical operators linked list
 *@head: the head of the liked list
 *Return: void
 */

void Free_log(log *head)
{
	log *current, *tmp;

	if (head == NULL)
	{
		return;
	}

	current = head;

	while (current)
	{
		free(current->com);
		tmp = current->next;
		free(current);
		current = tmp;
	}
}
