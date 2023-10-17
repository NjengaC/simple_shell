#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define SHELL_PATH "/bin:/usr/bin"
#define MAX_ALIASES 50

extern char **environ;

/**
 * struct Alias - structure of aliases
 * @name: name member
 * @value: value member
 *
 * Description: stores the name and value of aliases
 */

struct Alias
{
	char *name;
	char *value;
};
struct Alias aliases[MAX_ALIASES];

int reset(char ***argv, char **first, char **command);
char *get_exe(char *command);
char *c_strtok(char *strn, const char *delimiter);
int handle_builtins(char **av, char *command);
int _strcmp(char *str1, char *str2);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
int _strchr(char *s, char c);
int _putchar(char c);
int _atoi(char *s);
int execute(char **commands);
int execute_and(char **commands);
char *_strdup(const char *str);
ssize_t _igetline(char **lineptr, size_t *n, FILE *stream);
char **_strtok(char *input, const char *delim);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
int _chdir(char **av);
void free_str(char *str);
void free_sarray(char **av);
int whitespace(char *command);
char **tokenize(char *input);
char **tokenize_and(char *input);
char **tokenize_separator(char *input);
int check_inbuilts(char *input);
int handle_operators(char **commands, char *copy);
int execute_or(char **commands);
int handle_alias(char **av);
int add_alias(const char *name, const char *value);
int remove_alias(const char *name);
void list_aliases(void);
const char *lookup_alias(const char *name);
/*void cleanup_shell(void);*/
char *handle_replace(char *command);
char *itoa(int num);
char *tokenize_hash(char *input);
int execute_hash(char *command);
#endif
