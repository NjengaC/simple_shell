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

#define BUFFER_SIZE 1024
#define SHELL_PATH "/bin:/usr/bin"

extern char **environ;

int reset(char ***argv, char **first, char **command, int *count);
char *get_exe(char *command);
char *c_strtok(char *strn, const char *delimiter);
int handle_builtins(char **av, char *command);
int _strcmp(char *str1, char *str2);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
char *_strchr(char *s, char c);
int _putchar(char c);
int _atoi(char *s);
char *_strdup(const char *str);
ssize_t _igetline(char **lineptr, size_t *n, FILE *stream);
char **_strtok(char *input, const char *delim);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
int _chdir(char **av);
void free_str(char *str);
void free_sarray(char **av);
int whitespace(char *command);

#endif
