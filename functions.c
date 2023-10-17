#include "shell.h"
/**
 * _atoi - converts a string to an integer
 * @s: string to convert
 *
 * Return: the int converted from the string
 */

int _atoi(char *s)
{
	int i, d, n, len, f, digit;

	i = 0;
	d = 0;
	n = 0;
	len = 0;
	f = 0;
	digit = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	while (i < len && f == 0)
	{
		if (s[i] == '-')
		{
			++d;
		}
		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (d % 2)
			{
				digit = -digit;
			}
			n = n * 10 + digit;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
			{
				break;
			}
			f = 0;
		}
		i++;
	}
	if (f == 0)
	{
		return (0);
	}
	return (0);
}
/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
	int i = 0;

	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

/**
 * char *_strcpy - a function that copies the string pointed to by src
 * @dest: copy to
 * @src: copy from
 * Return: string
 */
char *_strcpy(char *dest, char *src)
{
	int l = 0;
	int x = 0;

	while (*(src + l) != '\0')
	{
		l++;
	}
	for ( ; x < l ; x++)
	{
		dest[x] = src[x];
	}
	dest[l] = '\0';
	return (dest);
}
/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 *
 *Return: difference of the strings
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
		{
			return (*str1 - *str2);
		}
		str1++;
		str2++;
	}

	return (*str1 - *str2);
}
/**
 * c_strtok - tokenizes a string and returns an null-terminated strings
 * @strn: string to break into tokens
 * @delimiter: delimiter
 * Return: null-terminated strings
 */

char *c_strtok(char *strn, const char *delimiter)
{
	static char *last_token;
	char *first_token, *end_token;
	ssize_t i;

	if (strn != NULL)
		last_token = strn;
	else if (last_token == NULL || *last_token == '\0')
		return (NULL);

	first_token = last_token;
	end_token = NULL;
	while (*last_token != '\0')
	{
		bool isdelim = false;

		for (i = 0; delimiter[i] != '\0'; i++)
		{
			if (*last_token == delimiter[i])
			{
				isdelim = true;
				break;
			}
		}
		if (isdelim)
		{
			*last_token = '\0';
			end_token = last_token + 1;
			last_token++;
			break;
		}
		last_token++;
	}
	if (end_token == NULL)
	{
		end_token = last_token;
	}
	last_token = end_token;
	return (first_token);
}
