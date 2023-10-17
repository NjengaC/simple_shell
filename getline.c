#include "shell.h"

/**
 *Itoa- changes from integer to string
 *@n: the number
 *Return: a string of the number
 */

char *Itoa(int n)
{
	unsigned int n1, temp;
	char *buffer;
	int i, length = 1;

	if (n < 0)
	{
		length++, n1 = (unsigned int)(-n);
	}
	else
	{
		n1 = (unsigned int)n;
	}
	temp = n1;
	while (temp /= 10)
	{
		length++;
	}
	buffer = (char *)malloc((length + 1) * sizeof(char));
	if (buffer == NULL)
	{
		return (NULL);
	}
	buffer[length] = '\0';
	if (n < 0)
	{
		buffer[0] = '-';
	}
	for (i = length - 1; i >= 0; i--)
	{
		buffer[i] = (n1 % 10) + '0', n1 /= 10;
	}

	return (buffer);
}

/**
 *Strdup - dublicates a string
 *@s: the string to be dublictated
 *Return: a dublicated string
 */

char *Strdup(const char *s)
{
	size_t len;
	const char *ptr;
	char *copy, *copy_ptr;

	if (s == NULL)
	{
		return (NULL);
	}
	len = 0, ptr = s;
	while (*ptr != '\0')
	{
		len++;
		ptr++;
	}
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == NULL)
	{
		free(copy);
		return (NULL);
	}
	ptr = s;
	copy_ptr = copy;
	while (*ptr != '\0')
	{
		*copy_ptr = *ptr;
		copy_ptr++;
		ptr++;
	}
	*copy_ptr = '\0';
	return (copy);
}

/**
 *Strcmp - compares two strings
 *@s1: the first character
 *@s2: the second string
 *Return: 0 if they match else 1
 */

int Strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}


/**
 *Strcpy - copies a string
 *@dest: the destination
 *@src:  the source
 *Return: the copied string
 */

char *Strcpy(char *dest, const char *src)
{
	char *dest_start = dest;

	while (*src != '\0')
		*dest++ = *src++;

	*dest = '\0';

	return (dest_start);
}

/**
 *Strcat - concatenates two strings
 *@dest: the destination
 *@src: the source string
 *Return: the concanted string
 */

char *Strcat(char *dest, const char *src)
{
	char *dest_start = dest;

	while (*dest != '\0')
		dest++;

	while (*src != '\0')
		*dest++ = *src++;

	*dest = '\0';

	return (dest_start);
}
