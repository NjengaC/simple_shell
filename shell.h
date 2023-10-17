#ifndef MAIN_H
#define MAIN_H

extern char **environ;


#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>



/**
 * struct SHELL - This struct represents the shell environment and stores info
 * on the shell's state.
 * @av: An array of strings representing the command-line arguments passed
 * to the shell.
 * @toks: An array of strings representing the tokens of the current command
 * input.
 * @pid: An integer representing the process ID of the current process.
 * @status: An integer representing the exit status of the last executed
 * command.
 * @_environ: An array of strings.
 * @loop_count: An integer representing the number of times the shell has
 * executed its main loop.
 */

typedef struct SHELL
{
	char **av;
	char **toks;
	int pid;
	int status;
	char **_environ;
	int loop_count;
} SHELL;


/**
 * struct builtincommands - This struct stores built-in commands in the shell.
 * @command: A string representing the name of the built-in command.
 * @function: A function pointer to the function that executes
 * the built-in command.
 */

typedef struct builtincommands
{
	char *command;
	void (*function)(SHELL *);
} builtin;



/**
 * struct log - This struct represents a node in a linked list used to store
 * logical operators in a command line.
 * @com: A string representing the command associated with the node.
 * @sep: A character representing the logical operator separator.
 * @next: A pointer to the next node in the linked list.
 */

typedef struct log
{
	char *com;
	char sep;
	struct log *next;
} log;

			/* PROCESS FUNCTIONS */
void handle_sigint(int signum __attribute__((unused)));
void env_extract(SHELL *shell);
void fill_eshell(SHELL *eshell);
void Frees(SHELL *eshell);
void Write(char *input);
void Fork(char *input, SHELL *shell);
void Command_unfound(SHELL *shell);
void path_error(SHELL *shell);
void Log(log **head, char *command);
void En_passant(SHELL *shell, log **current);
void shuffle(char *line, int mode);
void Free_log(log *head);
void seperator(log **head, char *line);
void handle_file(SHELL *shell);
void write_error(char *error, SHELL *shell);
void extension(char *nextToken, const char *delim, int *isDelimiter);

char *replacer(char *input, char *new, char *copy, char *ename);
char **tokenize(char *line, int mode);
char *hash(char *buffer);
char *Which(char *input);
char *_strtok(char *str, const char *delim);
char *Itoa(int n);
char *global_var(char *input __attribute__ ((unused)), SHELL *shell);
char *exit_status(char *input, char *status);
char *identity(char *input, char *id);
char *En_var(char *input, SHELL *shell);

int source(SHELL *shell, char *line);
int executables(char *input);
int process(SHELL *shell __attribute__ ((unused)));
int Access(char *input, SHELL *shell);
int First(char *input, SHELL *shell);
int Syntax(char *input, SHELL *shell);
int Syntax_error(char *input, SHELL *shell);
int Pipe(char *input, SHELL *shell);
int ampersand(char *input, SHELL *shell);

/* Handles builtin commands */

void change_dir_command(SHELL *shell);
void exit_command(SHELL *shell);
void env_command(SHELL *shell);
int handle_builtin_commands(SHELL *shell);


char *getenv_custom(const char *name);
int Atoi(const char *nptr);
char *Strcat(char *dest, const char *src);
char *Strcpy(char *dest, const char *src);
int Strcmp(const char *s1, const char *s2);
char *Strdup(const char *s);
void *Realloc(void *ptr, size_t old_size, size_t size);
char *Getline();
int Strlen(char *input);
size_t my_strlen(const char *s);

#endif
