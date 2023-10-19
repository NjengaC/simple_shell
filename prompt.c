#include "shell.h"


/**
 * handle_sigint - Function that handles CTRL C
 * @signum:It represents the single number that triggers the signal.
 *
 * Return: void
 */

void handle_sigint(int signum __attribute__((unused)))
{
	write(STDOUT_FILENO, "\n", 1);
	if (isatty(STDIN_FILENO))
	{
		Write("<TINKER> ");
		fflush(stdout);
	}
}

/**
 *main - entry point
 *@ac: the arguement count
 *@argv: the argurment vector
 *Return: status of the exectutions
 */

int main(int ac __attribute__ ((unused)), char **argv)
{
	char *line;
	int mode = 1;
	SHELL eshell;

	eshell.av = argv;
	fill_eshell(&eshell);

	if (argv[1])
	{
		handle_file(&eshell);
	}
	signal(SIGINT, handle_sigint);

	while (mode)
	{
		line = NULL;
		eshell.loop_count++;

		if (isatty(STDIN_FILENO))
			Write("<#cisfun$> ");

		line = Getline();
		line = global_var(line, &eshell);

		if (line[0] == '\0' || !line)
		{
			continue;
		}

		if (Syntax(line, &eshell) == -1)
		{
			free(line);
			continue;
		}

		mode = source(&eshell, line);
		free(line);
		line = NULL;
	}
	return (eshell.status);
}


/**
 * fill_eshell - Function that fills the struct members with respective
 * content.
 * @eshell: The struct to be filled.
 *
 * Return: Void.
 */

void fill_eshell(SHELL *eshell)
{
	eshell->pid = getpid();
	eshell->status = 0;
	eshell->_environ = NULL;
	eshell->loop_count = 0;
}


/**
 * Write - Function that writes whatver content given to the POSIX.
 * @input: Pointer to the content to be written out.
 *
 * Return: Void.
 */

void Write(char *input)
{
	int i;

	for (i = 0; input[i]; i++)
		;

	write(STDOUT_FILENO, input, i);
}
/**
 *seperator - determines what command should be executed next
 *@head: the head of the linked list
 *@line: the tokenized command
 *Return: nothing
 */

void seperator(log **head, char *line)
{
	int i;
	log *current;
	char a;


	shuffle(line, 1);
	current = *head;

	for (i = 0; line[i]; i++)
	{
		a = line[i];

		if (a == '|')
		{
			current->sep = '|';
			current = current->next;
		}

		else if (a == '&')
		{
			current->sep = '&';
			current = current->next;
		}

		else if (a == ';')
		{
			current->sep = ';';
			current = current->next;
		}

	}

	shuffle(line, 2);
}
