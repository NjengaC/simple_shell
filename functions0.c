#include "shell.h"
/**
 * _strchr - function checks occurence of a character
 * @s: name of string containing character
 * @c: character to locate
 *
 * Return: 0 on (Success) else return the character
 */

char *_strchr(char *s, char c)

{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == c)
			return (&s[i]);
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
